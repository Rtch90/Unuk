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

class Coordinate {
  int coordX;
  int coordY;
  int coordZ;

  std::string name;

public:
  Coordinate(void) : coordX(0), coordY(0), coordZ(0), name("") {}

  inline void* operator new(size_t size) {
    return gMemManager.Allocate(sizeof(Coordinate));
  }

  inline void operator delete(void* object) {
    gMemManager.Free(object);
  }
};

class Scheduler {
  std::vector<int> jobNumber;
  std::vector<int> maxJobTime;
  int              startTime;

public:
  Scheduler(void) {}

  inline void* operator new(size_t size) {
    return gMemManager.Allocate(sizeof(Scheduler));
  }

  inline void operator delete(void* object) {
    gMemManager.Free(object);
  }
};

const int SCHEDULER_SIZE    = sizeof(Scheduler);
const int COMPLEX_SIZE      = sizeof(Complex);
const int COORDINATE_SIZE   = sizeof(Coordinate);
// Number of elements in a single pool can be chosen on
// application requirement.
const int POOL_SIZE         = 1024;
// Depending on the application this may change.
const int MAX_BLOCK_SIZE    = 36;

#endif
