#include "MemClass.h"
#include "MemManager.h"

MemManager gMemManager;

void BitMapEntry::SetBit(int position, bool flag) {
  blocksAvailable += flag ? 1 : -1;
  int elementNo = position / INT_SIZE;
  int bitNo = position % INT_SIZE;
  if(flag)
    bitMap[elementNo] = bitMap[elementNo] | (1 << bitNo);
  else
    bitMap[elementNo] = bitMap[elementNo] & ~(1 << bitNo);
}

void BitMapEntry::SetMultipleBits(int position, bool flag, int count) {
  blocksAvailable += flag ? count : -count;
  int elementNo = position / INT_SIZE;
  int bitNo = position % INT_SIZE;

  int bitSize = (count <= INT_SIZE - bitNo) ? count : INT_SIZE - bitNo;
  SetRangeOfInt(&bitMap[elementNo], bitNo + bitSize - 1, bitNo, flag);
  count -= bitSize;
  if(!count) return;

  int i = ++elementNo;
  while(count >= 0) {
    if(count <= INT_SIZE) {
      SetRangeOfInt(&bitMap[i], count - 1, 0, flag);
      return;
    } else
      bitMap[i] = flag ? unsigned (-1) : 0;
    count -= 32;
    i++;
  }
}

void BitMapEntry::SetRangeOfInt(int* element, int msb, int lsb, bool flag) {
  if(flag) {
    int mask = (unsigned(-1) << lsb) & (unsigned(-1) >> (INT_SIZE - msb - 1));
    *element |= mask;
  } else {
    int mask = (unsigned(-1) << lsb) & (unsigned(-1) >> (INT_SIZE - msb - 1));
    *element &= ~mask;
  }
}

MemClass* BitMapEntry::FirstFreeBlock(size_t/* size*/) {
  for(int i = 0; i < BIT_MAP_ELEMENTS; i++) {
    if(bitMap[i] == 0)
      // There aint any bits free.
      continue;

    // Yield the first bit position. This is a 1
    // in an int from the right.
    int result = bitMap[i] & -(bitMap[i]);
    //void* address = 0;
    int basePos = (INT_SIZE * i);

    switch(result) {
      // Make the corresponfing bit 0 so block is no longer free.
    case 0x00000001: return ComplexObjectAddress(basePos + 0);
    case 0x00000002: return ComplexObjectAddress(basePos + 1);
    case 0x00000004: return ComplexObjectAddress(basePos + 2);
    case 0x00000008: return ComplexObjectAddress(basePos + 3);
    case 0x00000010: return ComplexObjectAddress(basePos + 4);
    case 0x00000020: return ComplexObjectAddress(basePos + 5);
    case 0x00000040: return ComplexObjectAddress(basePos + 6);
    case 0x00000080: return ComplexObjectAddress(basePos + 7);
    case 0x00000100: return ComplexObjectAddress(basePos + 8);
    case 0x00000200: return ComplexObjectAddress(basePos + 9);
    case 0x00000400: return ComplexObjectAddress(basePos + 10);
    case 0x00000800: return ComplexObjectAddress(basePos + 11);
    case 0x00001000: return ComplexObjectAddress(basePos + 12);
    case 0x00002000: return ComplexObjectAddress(basePos + 13);
    case 0x00004000: return ComplexObjectAddress(basePos + 14);
    case 0x00008000: return ComplexObjectAddress(basePos + 15);
    case 0x00010000: return ComplexObjectAddress(basePos + 16);
    case 0x00020000: return ComplexObjectAddress(basePos + 17);
    case 0x00040000: return ComplexObjectAddress(basePos + 18);
    case 0x00080000: return ComplexObjectAddress(basePos + 19);
    case 0x00100000: return ComplexObjectAddress(basePos + 20);
    case 0x00200000: return ComplexObjectAddress(basePos + 21);
    case 0x00400000: return ComplexObjectAddress(basePos + 22);
    case 0x00800000: return ComplexObjectAddress(basePos + 23);
    case 0x01000000: return ComplexObjectAddress(basePos + 24);
    case 0x02000000: return ComplexObjectAddress(basePos + 25);
    case 0x04000000: return ComplexObjectAddress(basePos + 26);
    case 0x08000000: return ComplexObjectAddress(basePos + 27);
    case 0x10000000: return ComplexObjectAddress(basePos + 28);
    case 0x20000000: return ComplexObjectAddress(basePos + 29);
    case 0x40000000: return ComplexObjectAddress(basePos + 30);
    case 0x80000000: return ComplexObjectAddress(basePos + 31);
    default: break;
    }
  }
  return 0;
}

MemClass* BitMapEntry::ComplexObjectAddress(int pos) {
  SetBit(pos, false);
  return &((static_cast<MemClass*>(Head()) + (pos / INT_SIZE)) [INT_SIZE - (pos % INT_SIZE + 1)]);
}

void* BitMapEntry::Head(void) {
  return gMemManager.GetMemoryPoolList()[index];
}

void* MemManager::Allocate(size_t size) {
  // None array.
  if(size == sizeof(MemClass)) {
    set<BitMapEntry*>::iterator freeMapI = _freeMapEntries.begin();
    if(freeMapI != _freeMapEntries.end()) {
      BitMapEntry* mapEntry = *freeMapI;
      return mapEntry->FirstFreeBlock(size);
    } else {
      AllocateChunkAndInitBitMap();
      _freeMapEntries.insert(&(_bitMapEntryList[_bitMapEntryList.size() - 1]));
      return _bitMapEntryList[_bitMapEntryList.size() - 1].FirstFreeBlock(size);
    }
  } else {
    // Array.
    if(_arrayMemoryList.empty()) {
      return AllocateArrayMemory(size);
    } else {
      map<void*, ArrayMemoryInfo>::iterator infoI    = _arrayMemoryList.begin();
      map<void*, ArrayMemoryInfo>::iterator infoEndI = _arrayMemoryList.end();

      while(infoI != infoEndI) {
        ArrayMemoryInfo info = (*infoI).second;
        if(info.StartPosition != 0)
          // Only search the memory blocks where allocation
          // is done from first byte.
          continue;
        else {
          BitMapEntry* entry = &_bitMapEntryList[info.memPoolListIndex];
          if(entry->blocksAvailable < (size / sizeof(MemClass)))
            return AllocateArrayMemory(size);
          else {
            info.StartPosition = BIT_MAP_SIZE - entry->blocksAvailable;
            info.Size = size / sizeof(MemClass);
            MemClass* baseAddress = static_cast<MemClass*>(_memoryPoolList[info.memPoolListIndex]) + info.StartPosition;

            _arrayMemoryList[baseAddress] = info;
            SetMultipleBlockBits(&info, false);

            return baseAddress;
          }
        }
      }
    }
  }
  return 0;
}

void* MemManager::AllocateArrayMemory(size_t size) {
  void* chunkAddress = AllocateChunkAndInitBitMap();
  ArrayMemoryInfo info;
  info.memPoolListIndex = _memoryPoolList.size() - 1;
  info.StartPosition = 0;
  info.Size = size / sizeof(MemClass);
  _arrayMemoryList[chunkAddress] = info;
  SetMultipleBlockBits(&info, false);
  return chunkAddress;
}

void* MemManager::AllocateChunkAndInitBitMap(void) {
  BitMapEntry mapEntry;
  MemClass* memoryBeginAddress = reinterpret_cast<MemClass*>(new char[sizeof(MemClass) * BIT_MAP_SIZE]);
  _memoryPoolList.push_back(memoryBeginAddress);
  mapEntry.index = _memoryPoolList.size() - 1;
  _bitMapEntryList.push_back(mapEntry);
  return memoryBeginAddress;
}

void MemManager::Free(void* object) {
  if(_arrayMemoryList.find(object) == _arrayMemoryList.end())
    // Simple block deletion.
    SetBlockBit(object, true);
  else {
    // Memory block deletion.
    ArrayMemoryInfo *info = &_arrayMemoryList[object];
    SetMultipleBlockBits(info, true);
  }
}

void MemManager::SetBlockBit(void* object, bool flag) {
  int i = _bitMapEntryList.size() - 1;
  for(; i >= 0; i--) {
    BitMapEntry* bitMap = &_bitMapEntryList[i];
    if((bitMap->Head() <= object) && (&(static_cast<MemClass*>(bitMap->Head()))[BIT_MAP_SIZE - 1] >= object)) {
      int position = static_cast<MemClass*>(object)- static_cast<MemClass*>(bitMap->Head());
      bitMap->SetBit(position, flag);
      flag ? bitMap->blocksAvailable++ : bitMap->blocksAvailable--;
    }
  }
}

void MemManager::SetMultipleBlockBits(ArrayMemoryInfo* info, bool flag) {
  BitMapEntry* mapEntry = &_bitMapEntryList[info->memPoolListIndex];
  mapEntry->SetMultipleBits(info->StartPosition, flag, info->Size);
}

vector<void*>& MemManager::GetMemoryPoolList(void) {
  return _memoryPoolList;
}
