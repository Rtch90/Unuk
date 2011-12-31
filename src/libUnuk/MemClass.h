#ifndef _MEMCLASS_H_
#define _MEMCLASS_H_
#include <string>
#include <vector>
#include "MemManager.h"

extern MemManager gMemManager;

class Complex {
public:
  Complex(void) : r(0), c(0) {}
  Complex(double a, double b): r(a), c(b) {}

  inline void* operator new(size_t size) {
    return gMemManager.Allocate(sizeof(Complex));
  }

  inline void operator delete(void* object) {
    gMemManager.Free(object);
  }

private:
  // Real part.
  double r;
  // Complex part.
  double c;
};

#endif
