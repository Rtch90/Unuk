#ifndef _NODE_H_
#define _NODE_H_
#include <memory.h>

#ifndef NULL
#define NULL 0
#endif

#define NL_ADDOPEN	0
#define NL_STARTOPEN	1
#define	NL_DELETEOPEN	2
#define NL_ADDCLOSED	3

#define NC_INITIALADD	0
#define NC_OPENADD_UP	1
#define NC_OPENADD	2
#define NC_CLOSEDADD_UP 3
#define NC_CLOSEADD 	4
#define NC_NEWADD	5

class Node {
public:
  Node(int posx = -1, int posy = -1) : x(posx), y(posy), id(0), numChildren(0) {
    parent = next = NULL;
    memset(children, 0, sizeof(children));
  }
  
  // Fitness, goal, heuristic.
  int f, g, h; 
  // Position x and y.
  int x, y;
  int numChildren; // x*m_rows+y
  int id;

  Node *parent;
  Node *next;
  // Square tiles.
  Node *children[8];
};

struct Stack {
  Node  *data;
  Stack *next;
};

typedef int(*Func) (Node *, 	 Node *, int, void *); 
                            	
#endif
