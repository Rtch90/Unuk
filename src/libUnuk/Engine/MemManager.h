#pragma once

#ifndef INCLUDED_NEW
#define INCLUDED_NEW
#include <new>
#endif

class MemManager {
  // Not implemented.
  MemManager(void);
  ~MemManager(void);

public:
  // Affect behavior.
  static void SetFailingPercentage(int percentage);

  // Pointers.
  static void ValidatePointer(void* pointer);
  static void ValidateAllPointers(void);
  static int AmountOfMemoryAllocated(void* pointer, bool includeManagerExtra = false);
  static int AmountOfMemoryInUse(void* pointer);

  // Logging.
  static void LogStatistics(const char* filename);
  static void LogUnusedPointers(const char* filename, float freePercentage);

  // Memory statistics.
  static int AmountOfMemoryInUse(bool includeManagerExta = false);
  static int AmountOfPeakMemoryInUse(bool includeManagerExtra = false);
  static int AmountOfMemoryAllocations(void);
  static int AmountOfPeakMemoryAllocations(void);
};

// Quick hack to get some extra information about allocations.
void DebugSetAllocationInfo(const char* allocationInfo);
void DumpLeakSnapshot(bool fromStart = false);
void MarkLeakSnapshot(void);

// Global operators.
void* operator new(size_t size, const char* filename, int lineNumber) throw(std::bad_alloc);
void* operator new(size_t size) throw(std::bad_alloc);
void* operator new[](size_t size, const char* filename, int lineNumber) throw(std::bad_alloc);
void* operator new[](size_t size) throw(std::bad_alloc);
void operator delete(void* buffer) throw();
void operator delete[](void* buffer) throw();

// I don't think there are any compilers that don't define these, but just in case.
#ifndef __FILE__
#define __FILE__ "???"
#endif
#ifndef __LINE__
#define __LINE__ 0
#endif

#ifndef _MSC_VER
#define new(__FILE__, __LINE__)
#endif
