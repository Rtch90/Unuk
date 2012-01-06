#ifndef _NODE_H_
#define _NODE_H_
#include <vector>
#include <iostream>

class Node {
public:
  Node(int xArg, int yArg);
  virtual ~Node(void);

  inline int GetX(void) const { return x; }
  inline int GetY(void) const { return y; }
  inline float GetCost(void)  { return _cost; }

private:
  int x, y;
  float _cost;
};

#endif
