#ifndef _ASTAR_H_
#define _ASTAR_H_
#include "Node.h"

class AStar {
public:
  AStar(void);
  ~AStar(void);

  Func udCost;		// Called when the cost is needed.
  Func udValid;		// Check the validity of the coordanate.
  Func udNotifyChild;	// Child is called/checked (LinkChild).
  Func udNotifyList; 	// node is added to the open/closed list.

  void *CBData;		// Data passed back to the callback function.
  void *NCData; 	// Data paseed back to to notify child.

  bool GeneratePath(int startx, int starty, int destx, int desty);
  int Step(void);
  int InitStep(int startx, int starty, int destx, int desty);
  void SetRows(int r) { m_rows = r; }
  void Reset(void) { m_best = NULL; } 
  
  Node *GetBestNode(void) { return m_best; }
  
private:
  int m_rows; // Used to calculate unique ID for node->number.
  int m_startx;
  int m_starty;
  int m_destx;
  int m_desty;

  int m_ID;
  

  // Node list.
  Node *m_open;
  Node *m_closed;
  Node *m_best;

  Stack *m_stack;

  // Private methods.
  void AddToOpen(Node *node);
  void ClearNodes(void);
  void CreateChildren(Node *node);
  void LinkChild(Node *, Node *);
  void UpdateParent(Node *node);

  // Stack functions.
  void Push(Node *node);
  Node *Pop(void);
  Node *CheckList(Node *node, int number);
  Node *GetBest(void);

  inline int Coord2Id(int x, int y) { return x * m_rows + y; }  
};

#endif
