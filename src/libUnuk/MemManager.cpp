#include "MemManager.h"
#include "MemClass.h"

MemManager gMemManager;

MemManager::MemManager(void) {

}

MemManager::~MemManager(void) {

}

void* MemManager::Allocate(size_t size) {
  void* base = 0;
  switch(size) {
  case SCHEDULER_SIZE:    { // 28
      if(_byte32PtrList.empty()) {
        base = new char[32 * POOL_SIZE];
        _memoryPoolList.push_back(base);
        InitByte32List(base);
      }
      void* blockPtr = _byte32PtrList.front();
      // Size of block set.
      *((static_cast<char*>(blockPtr)) + 30) = 32;
      // Block is no longer free.
      *((static_cast<char*>(blockPtr)) + 31) = 0;
      _byte32PtrList.pop_front();
      return blockPtr;
    }

  case COORDINATE_SIZE: { // 36
      if(_byte40PtrList.empty()) {
        base = new char[40 * POOL_SIZE];
        _memoryPoolList.push_back(base);
        InitByte40List(base);
      }
      void* blockPtr = _byte40PtrList.front();
      // Size of block set.
      *((static_cast<char*>(blockPtr)) + 38) = 40;
      // Block is no longer free.
      *((static_cast<char*>(blockPtr)) + 39) = 0;
      _byte40PtrList.pop_front();
      return blockPtr;
    }

  case COMPLEX_SIZE: { // 16
      if(_byte24PtrList.empty()) {
        base = new char[24 * POOL_SIZE];
        _memoryPoolList.push_back(base);
        InitByte24List(base);
      }
      void* blockPtr = _byte24PtrList.front();
      // Size of block set.
      *((static_cast<char*>(blockPtr)) + 22) = 32;
      // Block is no longer free.
      *((static_cast<char*>(blockPtr)) + 23) = 0;
      _byte24PtrList.pop_front();
      return blockPtr;
    }
  default:
    break;
  }
  return 0;
}
