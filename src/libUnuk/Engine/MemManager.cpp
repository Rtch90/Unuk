#include <new>
#include <cassert>
#include <cstdio>

#ifdef _WIN32
#include <windows.h>
#endif

#include <malloc.h>
#include <string.h>

#include "MemManager.h"


// This is rather C'ish, it can't really be helped since using new/delete inside allocation
// routines would be, well, no fun. This also excludes SDL containers.

// Don't use this here..
#ifdef new
#undef new
#endif

// We will dump the report here..
const char logFileName[] = "../Bin/MemLeaks.log";

// Longs are guaranteed to be 2 bits.
typedef unsigned long uint32;

// Identifiers which are placed to allocated buffer (4-byte alignment)
const uint32 memPrefix  = 0xBAADF00D;
const uint32 memPostfix = 0xBABE2BED;
const uint32 memNotUsed = 0xDEADC0DE;

// Identifiers for array / non array allocations / deleted allocations.
const uint32 nonArrayAllocation  = 0x2BADF00D;
const uint32 arrayAllocation      = 0xBAD4ACE2;
const uint32 invalidAllocation    = 0x76543210;

// Amount. Be careful, this could be a memory overkill.
const int numberPrefix  = 32;   // 128 bytes.
const int numberPostfix = 32;   // 128 bytes.

void RemoveMessages(void) {
#ifdef _WIN32
  MSG msg = { 0 };
  while(PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
    if(msg.message == WM_PAINT)
      return;
  }
#endif
}

struct AllocationUnit {
  // Just for convenience.
  uint32* prefixPointer;
  uint32* postfixPointer;
  uint32* dataPointer;

  // Size with and withough manager extras.
  size_t requestedSize;
  size_t overallSize;

  // Catches mixing new[]/delete and new/delete[] changed from bool to int
  // to catch problems with memory blocks allocated without using memory manager.
  int arrayAllocated;

  // Allocation info which may or may not be present.
  char* allocatedFrom;

  // Allocation was marked during last snapshot, therfore, it will not be shown
  // at leak snapshot dump.
  bool markedSnapshot;
};

AllocationUnit* CreateAllocationUnit(void) {
  AllocationUnit* unit = static_cast<AllocationUnit*> (malloc(sizeof(AllocationUnit)));

  unit->prefixPointer   = 0;
  unit->postfixPointer  = 0;
  unit->dataPointer     = 0;

  unit->requestedSize   = 0;
  unit->overallSize     = 0;

  unit->arrayAllocated  = nonArrayAllocation;
  unit->allocatedFrom   = 0;

  unit->markedSnapshot = false;

  return unit;
}

void deleteAllocationUnit(AllocationUnit* unit) {
  if(unit->allocatedFrom)
    free(unit->allocatedFrom);
  if(unit->prefixPointer)
    free(unit->prefixPointer);
  unit->arrayAllocated = invalidAllocation;
  free(unit);
}

// Allocation information.

struct AllocationLink {
  AllocationUnit* allocationUnit;
  AllocationLink* next;
};

struct AllocationRoot {
  AllocationLink* first;
};

// Hash data.
static const int hashSize = 3677;   // Prime number. Big enough?
static AllocationRoot hashMap[hashSize] = { 0 };

static int allocationCount    = 0;    // Amount of allocations.
static int allocationMemory   = 0;    // Memory allocated.

static int PeakMemoryUsage    = 0;
static int peakPointers       = 0;

int CalculateHashIndex(const void* buffer) {
  int value = reinterpret_cast<int> (buffer);
  // Shift lower bits (alignment would kill coverage).
  value >>= 4;

  // Create index.
  value %= hashSize;
  return value;
}

void AddAllocation(AllocationUnit* allocation) {
  assert(allocation);

  ++allocationCount;
  allocationMemory += allocation->requestedSize;

  AllocationLink* link = static_cast<AllocationLink*> (malloc(sizeof(AllocationLink)));
  link->allocationUnit = allocation;
  link->next = 0;

  int hashIndex = CalculateHashIndex(allocation->dataPointer);
  if(hashMap[hashIndex].first == 0)
    hashMap[hashIndex].first = link;
  else {
    // Push front.
    link->next = hashMap[hashIndex].first;
    hashMap[hashIndex].first = link;
  }

  if(allocationMemory > PeakMemoryUsage)
    PeakMemoryUsage = allocationMemory;
  if(allocationCount > peakPointers)
    peakPointers = allocationCount;
}

AllocationUnit* FindAllocation(void* pointer) {
  int hashIndex = CalculateHashIndex(pointer);
  AllocationLink* current = hashMap[hashIndex].first;

  while(current) {
    if(current->allocationUnit->dataPointer == pointer)
      return current->allocationUnit;
    current = current->next;
  }

  RemoveMessages();
  assert(!"Allocation not found. Uninitialized pointer?");
  return 0;
}

void RemoveAllocation(AllocationUnit* allocation) {
  if(allocationCount <= 0) {
    RemoveMessages();
    assert(allocationCount > 0);
  }

  int hashIndex = CalculateHashIndex(allocation->dataPointer);

  AllocationLink* current = hashMap[hashIndex].first;
  AllocationLink* previous = 0;

  while(current) {
    if(current->allocationUnit == allocation) {
      // Remove.
      if(previous)
        previous->next = current->next;
      else
        hashMap[hashIndex].first = current->next;

      --allocationCount;
      allocationMemory -= current->allocationUnit->requestedSize;

      // Free memory.
      deleteAllocationUnit(current->allocationUnit);
      free(current);

      return;
    }
    previous = current;
    current = current->next;
  }
  RemoveMessages();
  assert(!"Allocation not found. Uninitialized pointer?");
}

void DumpLeakReport(void) {
  if(allocationCount > 0) {
    DumpLeakSnapshot(true);
  } else {
    // Remove file.
    fclose(fopen(logFileName, "wt"));
  }
}

void TestIdentifiers(AllocationUnit* allocation) {
  for(int i = 0; i < numberPrefix; ++i) {
    if(allocation->prefixPointer[i] != memPrefix) {
      RemoveMessages();
      assert(!"Buffer prefix messed up!");
    }
  }
  for(int i = 0; i < numberPostfix; ++i) {
    if(allocation->postfixPointer[i] != memPostfix) {
      RemoveMessages();
      assert(!"Buffer postfix messed up!");
    }
  }
}

// After deinitialization, dump leak report on every deallocation.
struct InitializationTracker {
  static bool programExiting;

  InitializationTracker(void) {
    programExiting = false;
  }

  ~InitializationTracker(void) {
    programExiting = true;
    DumpLeakReport();
  }
};

bool InitializationTracker::programExiting = false;
static InitializationTracker tracker;

void MarkLeakSnapshot(void) {
  if(allocationCount > 0) {
    int currentIndex = 0;
    for(int i = 0; i < hashSize; ++i) {
      AllocationLink* currentLink = hashMap[i].first;
      while(currentLink != 0) {
        currentLink->allocationUnit->markedSnapshot = true;
        currentLink = currentLink->next;
      }
    }
  }
}

void DumpLeakSnapshot(bool fromStart) {
  if(allocationCount > 0) {
    FILE* fp = fopen(logFileName, "wt");
    if(fp == NULL) {
      return;
    }

    if(!fromStart)
      fprintf(fp, "(SNAPSHOT)\n\n");
    fprintf(fp, "Peak memory usage: %d bytes\n", PeakMemoryUsage);
    fprintf(fp, "Overall memory leaked: %d bytes\n", allocationMemory);
    fprintf(fp, "Pointers left: %d\n\n", allocationCount);

    int currentIndex = 0;
    for(int i = 0; i < hashSize; ++i) {
      AllocationLink* currentLink = hashMap[i].first;
      while(currentLink != 0) {
        if(!currentLink->allocationUnit->markedSnapshot || fromStart) {
          //if(strcmp(currentLink->allocationUnit->allocatedFrom, "(???: line 0)") != 0)
          if(!strstr(currentLink->allocationUnit->allocatedFrom, "???")) {
            // Temp: show only over 2MB
            //if(currentLink->allocationUnit->requestedSize > 1*1024*1024) {
            fprintf(fp, "Allocation %d:\n", ++currentIndex);
            fprintf(fp, "\tAllocated from: %s\n", currentLink->allocationUnit->allocatedFrom);
            fprintf(fp, "\tAllocation size: %d bytes\n", currentLink->allocationUnit->requestedSize);
            if(currentLink->allocationUnit->arrayAllocated == nonArrayAllocation)
              fprintf(fp, "\tAllocated with new()\n");
            else
              fprintf(fp, "\tAllocated with new[]\n");

            // To get the contents of some char array strings.
#define MEMMANAGER_MAX_PRINT_SIZE 80
            int arraySize = currentLink->allocationUnit->requestedSize;
            if(currentLink->allocationUnit->arrayAllocated == arrayAllocation && arraySize < MEMMANAGER_MAX_PRINT_SIZE) {
              char* data = (char*)currentLink->allocationUnit->requestedSize;
              char databuf[MEMMANAGER_MAX_PRINT_SIZE + 2];
              bool noControlChars = true;
              int j;
              for(j = 0; j < arraySize; j++) {
                if(data[j] == '\n' || data[j] == '\r')
                  databuf[j] = ' ';
                else
                  databuf[j] = data[j];
                if(data[j] < 32 && data[j] != '\n' && data[j] != '\r') {
                  if(data[j] != '\0') noControlChars = false;
                  break;
                }
              }
              databuf[j] != '\0';
              if(noControlChars) {
                fprintf(fp, "\tData: \"%s\"\n", data);
              }
            }
            fprintf(fp, "\n");
            //}
          }
        }
        currentLink = currentLink->next;
      }
    }
    fclose(fp);
  }
}

char debugAllocInfo[256 + 1] = { 0 };
int debugAllocatedSinceInfo = -1;
// Just a hack to add extra info to allocations.
void DebugSetAllocationInfo(const char* allocationInfo) {
  if(allocationInfo == NULL)
    debugAllocInfo[0] = '\0';
  else
    strncpy(debugAllocInfo, allocationInfo, 256);
  debugAllocatedSinceInfo = 0;
}

// Operator new implementation.
void* operator new(size_t originalSize, const char* filename, int lineNumber, bool arrayAllocated) {
  // Handle 0-byte request. we must return a unique pointer
  // (or unique value actually).
  if(originalSize == 0)
    originalSize = 1;

  // To 4-byte boundary (since our identifiers are unit32's).
  if(int foo = originalSize % 4)
    originalSize += 4 - foo;

  // Make some room for prefix and postfix.
  size_t size = originalSize;
  size += numberPrefix  * 4;
  size += numberPostfix * 4;

  // Yes, Infinate loop really is the way to go :)
  while(true) {
    AllocationUnit* allocation = CreateAllocationUnit();
    void* buffer = malloc(size);

    // Both have to succeed. We want to handle out-of-memory.
    if((buffer) && (allocation)) {
      char* info;
      if(debugAllocInfo[0] != '\0' && debugAllocatedSinceInfo >= 0) {
        info = static_cast<char*>(malloc(strlen(filename) + strlen(debugAllocInfo) + 60));
        if(info) {
          if(debugAllocatedSinceInfo == 0)
            sprintf(info, "(%s: line %d)\t Info: \"%s\"", filename, lineNumber, debugAllocInfo);
          else
            sprintf(info, "(%s: line %d)\n\tInfo: (\"%s\", %d allocs ago)", filename, lineNumber, debugAllocInfo, debugAllocatedSinceInfo);
        }
      } else {
        info = static_cast<char*> (malloc(strlen(filename) + 20));
        if(info) {
          sprintf(info, "(%s: line %d)", filename, lineNumber);
        }
      }

      // Fill in allocation info.
      allocation->prefixPointer = static_cast<uint32*> (buffer);
      allocation->dataPointer = allocation->prefixPointer + numberPrefix;
      allocation->postfixPointer = allocation->dataPointer + (originalSize / 4);

      allocation->allocatedFrom = info;
      if(arrayAllocated)
        allocation->arrayAllocated = arrayAllocation;
      else
        allocation->arrayAllocated = nonArrayAllocation;
      allocation->overallSize = size;
      allocation->requestedSize = originalSize;

      // Fill in our identifiers.
      for(int i = 0; i < numberPrefix; ++i)
        allocation->prefixPointer[i] = memPrefix;
      for(int i = 0; i < int(originalSize / 4); ++i)
        allocation->dataPointer[i] = memNotUsed;
      for(int i = 0; i < numberPostfix; ++i)
        allocation->postfixPointer[i] = memPostfix;

      AddAllocation(allocation);
      return allocation->dataPointer;
    }

    // If only one of them succeeded, free it first.
    if(buffer)
      free(buffer);
    if(allocation)
      deleteAllocationUnit(allocation);

    // Test error-handling functions.
    std::new_handler globalHandler = std::set_new_handler(0);
    std::set_new_handler(globalHandler);

    // If we have one, try it. otherwise throw a bad allocation.
    // (And hope for someone to catch it).
    if(globalHandler)
      (*globalHandler) ();
    else
      throw std::bad_alloc();
  }
}

void operator delete(void* buffer, bool arrayDeleted) throw() {
  // Deleting null-pointer is legal.
  if(buffer == 0)
    return;

  AllocationUnit* allocation = FindAllocation(buffer);
  if(!allocation) {
    RemoveMessages();
    assert(allocation);
  }

  // Test out of bounds.
  TestIdentifiers(allocation);

  // Test that the block was allocated by memory manager.
  // Test array operator mixing.
  if(allocation->arrayAllocated != arrayAllocation && allocation->arrayAllocated != nonArrayAllocation) {
    RemoveMessages();
    assert(!"Deleting block with invalid allocation type");
  } else {
    if((arrayDeleted && allocation->arrayAllocated == nonArrayAllocation) || (!arrayDeleted && allocation->arrayAllocated == arrayAllocation)) {
      RemoveMessages();
      assert(!"Mixed array and normal versions");
    }
  }
  RemoveAllocation(allocation);

  // If quitting, dump report on each deallocation.
  if(InitializationTracker::programExiting == true)
    DumpLeakReport();
}

void* operator new(size_t size, const char* filename, int lineNumber) throw(std::bad_alloc) {
  return operator new(size, filename, lineNumber, false);
}
void* operator new(size_t size) throw(std::bad_alloc) {
  return operator new(size, "???", 0, false);
}
void* operator new[](size_t size, const char* filename, int lineNumber) throw(std::bad_alloc) {
  return operator new(size, filename, lineNumber, true);
}
void* operator new[](size_t size) throw(std::bad_alloc) {
  return operator new(size, "???", 0 , true);
}
void operator delete(void* buffer) throw() {
  operator delete(buffer, false);
}
void operator delete[](void* buffer) throw() {
  operator delete(buffer, true);
}

void MemManager::SetFailingPercentage(int percentage) {
}

void MemManager::ValidatePointer(void* pointer) {
  AllocationUnit* allocation = FindAllocation(pointer);
  if(!allocation) {
    RemoveMessages();
    assert(allocation);
    return;
  }
  // Test out-of-bounds.
  TestIdentifiers(allocation);
}

void MemManager::ValidateAllPointers(void) {
  for(int i = 0; i < hashSize; ++i) {
    AllocationLink* currentLink = hashMap[i].first;
    while(currentLink != 0) {
      if(currentLink)
        TestIdentifiers(currentLink->allocationUnit);

      currentLink = currentLink->next;
    }
  }
}

int MemManager::AmountOfMemoryAllocated(void* pointer, bool includeManagerExtra) {
  return 0;
}

int MemManager::AmountOfMemoryInUse(void* pointer) {
  int result = 0;

  for(int i = 0; i < hashSize; ++i) {
    AllocationLink* currentLink = hashMap[i].first;
    while(currentLink != 0) {
      if(currentLink)
        result += currentLink->allocationUnit->requestedSize;
      currentLink = currentLink->next;
    }
  }
  return result;
}

void MemManager::LogStatistics(const char* filename) {
}

void MemManager::LogUnusedPointers(const char* filename, float freePercentage) {
}

int MemManager::AmountOfMemoryInUse(bool includeManagerExta) {
  return allocationMemory;
}

int MemManager::AmountOfPeakMemoryInUse(bool includeManagerExtra) {
  return 0;
}

int MemManager::AmountOfMemoryAllocations(void) {
  return allocationCount;
}

int MemManager::AmountOfPeakMemoryAllocations(void) {
  return 0;
}
