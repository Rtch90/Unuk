#ifndef _MEMCLASS_H_
#define _MEMCLASS_H_
#include "MemManager.h"

extern MemManager gMemManager;

class MemClass {
public:
  MemClass(void) : r(0), c(0) {}
  MemClass(double a, double b): r(a), c(b) {}

  inline void* operator new(size_t size) {
    return gMemManager.Allocate(size);
  }

  inline void operator delete(void* object) {
    gMemManager.Free(object);
  }

  inline void* operator new [](size_t size) {
    return gMemManager.Allocate(size);
  }

  inline void operator delete [](void* object) {
    gMemManager.Free(object);
  }

private:
  // Real part.
  double r;
  // Complex part.
  double c;
};

#endif
