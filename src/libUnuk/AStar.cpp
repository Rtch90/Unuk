#include "AStar.h"

AStar::AStar(void) {
  while(_openList.size() > 0) {
    _openList.pop();
  }
  _closedList.clear();
  _solution.clear();
}

AStar::~AStar(void) {
  AStarBase* best = 0;
  while(_openList.size() > 0) {
    best = _openList.top();
    _openList.pop();
    delete best;
  }
  _closedList.clear();
}

/*
 * Solved the situation given by the initial state with AStar,
 * and returns a vector of AStarBase that solves the problem.
 */
std::vector<AStarBase*> AStar::Solve(AStarBase* initState) {
  AStarBase* best = 0;
  while(_openList.size() > 0) {
    best = _openList.top();
    _openList.pop();
    delete best;
  }
  _closedList.clear();

  _openList.push(initState);
  return GetSolutionSequence(Search());
}

// Search for the best path.
AStarBase* AStar::Search(void) {
  AStarBase* best = 0;
  long key = 0;
  std::vector<AStarBase*> child;

  while(_openList.size() > 0) {
    while(_closedList.find(key) != _closedList.end()) {
      // Take the best state, and check if it is on the closed list.
      if(_openList.size() > 0) {
        best = _openList.top();
        _openList.pop();
      } else 
        return 0;

      key = best->CalculateKey();
    }
    
    // Put best on the closed list.
    _closedList[key] = best;

    // Check id best is our goal.
    if(best->isGoal())
      return best;

    // Generate the children.
    child = best->GenerateChildren();
    for(unsigned int i = 0; i < child.size(); i++) {
      _openList.push(child[i]);
    }
  }
  return 0;
}

// Generate a solution sequence for a given state.
std::vector<AStarBase*> AStar::GetSolutionSequence(AStarBase* node) {
  _solution.clear();
  AStarBase* state = node;

  while(state != 0) {
    _closedList.erase(state->_key);
    _solution.insert(_solution.begin(), state);
    state = state->_parent;
  }

  // Delete the states which are not part of the solution.
  while(_closedList.size() > 0) {
    state = _closedList.begin()->second;
    _closedList.erase(state->_key);
    delete state;
  }

  return _solution;
}

