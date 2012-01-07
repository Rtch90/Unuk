#ifndef _ASTARBASE_H_
#define _ASTARBASE_H_
#include <vector>

class AStarBase {
public:
  AStarBase(void) { };
  virtual ~AStarBase(void) { };

  // Generate a unique key.
  virtual long CalculateKey(void) = 0;

  // Aproximate the heuristic cost to the goal.
  virtual double Estimate(void) = 0;

  // Have we reached the goal?
  virtual bool isGoal(void) = 0;

  virtual std::vector<AStarBase*> GenerateChildren(void) = 0;

  AStarBase* _parent;

  double _pastCost;
  double _totalEstimatedCost;

  long _key;
};

#endif

