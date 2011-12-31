#ifndef _MEMMANAGER_H_
#define _MEMMANAGER_H_
#include <vector>
#include <set>
#include <list>
#include <stdio.h>
#include <vector>
#include <string>
using namespace std;

class IMemManager {
public:
  virtual void* Allocate(size_t size) = 0;
  virtual void  Free(void* ) = 0;
};

class MemManager : public IMemManager {
public:
  MemManager(void);
  ~MemManager(void);

  void* Allocate(size_t size);
  void  Free(void* object);

private:
  list<void*>    _byte8PtrList;
  list<void*>    _byte16PtrList;
  list<void*>    _byte24PtrList;
  list<void*>    _byte32PtrList;
  list<void*>    _byte40PtrList;
};

#endif
