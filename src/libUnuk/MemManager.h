#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <vector>
#include <set>
#include <map>
#include <bitset>
using namespace std;

const int BIT_MAP_SIZE   = 1024;
const int INT_SIZE      = sizeof(int) * 8;
const int BIT_MAP_ELEMENTS = BIT_MAP_SIZE / INT_SIZE;

/*
 * Memory Allocation Pattern.
 * 11111111 11111111 11111111
 * 11111110 11111111 11111111
 * 11111100 11111111 11111111
 *
 * If all bits for the first section becomes zero go to next section.
 *
 * 00000000 11111111 11111111
 * 00000000 11111110 11111111
 * 00000000 11111100 11111111
 * 00000000 11111000 11111111
 *
 * The lookup inside the map becomes 0(1) for the first available free block.
 */

class MemClass;

typedef struct BitMapEntry {
  int index;
  int blocksAvailable;
  int bitMap[BIT_MAP_SIZE];

public:
  BitMapEntry():blocksAvailable(BIT_MAP_SIZE) {
    // All blocks are free to begin with and bit value 1
    // in the map denotes available blocks.
    memset(bitMap, 0xff, BIT_MAP_SIZE / sizeof(char));
  }

  void SetBit(int position, bool flag);
  void SetMultipleBits(int position, bool flag, int count);
  void SetRangeOfInt(int* element, int msb, int lsb, bool flag);
  MemClass* FirstFreeBlock(size_t size);
  MemClass* ComplexObjectAddress(int pos);
  void* Head(void);
} BitMapEntry;

typedef struct ArrayInfo {
  int memPoolListIndex;
  int StartPosition;
  int Size;
} ArrayMemoryInfo;

class IMemManager {
public:
  virtual void* Allocate(size_t size) = 0;
  virtual void  Free(void* object)    = 0;
};

class MemManager : public IMemManager {
public:
  MemManager(void)  {}
  ~MemManager(void) {}

  void* Allocate(size_t size);
  void  Free(void* object);
  vector<void*>& GetMemoryPoolList(void);

private:
  void* AllocateArrayMemory(size_t size);
  void* AllocateChunkAndInitBitMap(void);
  void SetBlockBit(void* object, bool flag);
  void SetMultipleBlockBits(ArrayMemoryInfo* info, bool flag);

  // The following lists will maintain one to one correspondace
  // and should be the same size.
  vector<void*> _memoryPoolList;
  vector<BitMapEntry> _bitMapEntryList;

  set<BitMapEntry*> _freeMapEntries;
  map<void*, ArrayMemoryInfo> _arrayMemoryList;
};
