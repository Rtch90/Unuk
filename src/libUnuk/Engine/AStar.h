#pragma once
#include <vector>
#include <map>
#include <queue>

#include "AStarBase.h"

class AStar {
public:
  AStar(void);
  ~AStar(void);

  std::vector<AStarBase*> Solve(AStarBase* initState);

private:
  // Comparison structure.
  struct Cmp : public std::binary_function<AStarBase*, AStarBase*, bool> {
     bool operator()(AStarBase* a1, AStarBase* a2) const {
       return (a1->_totalEstimatedCost >= a2->_totalEstimatedCost);
     }
   };

  std::priority_queue<AStarBase*, std::vector<AStarBase*>, Cmp > _openList;
  std::map<const long, AStarBase*> _closedList;

  AStarBase* Search(void);

  std::vector<AStarBase*> GetSolutionSequence(AStarBase* node);
  std::vector<AStarBase*> _solution;
};
