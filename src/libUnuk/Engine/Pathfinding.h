#pragma once
#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

// Disable warning that debugging information has lines that are truncated.
#ifdef WIN32
#pragma warning(disable : 4786)
#endif

// The search class. UserState is the users state space type.
template<class UserState> class AStarSearch {
public:
	enum {
		SEARCH_STATE_NOT_INITIALIZED,
		SEARCH_STATE_SEARCHING,
		SEARCH_STATE_SUCCEEDED,
		SEARCH_STATE_FAILED,
		SEARCH_STATE_OUT_OF_MEMORY,
		SEARCH_STATE_INVALID
	};

	// A node representing a possible state in the search.
public:
	class Node {
	public:
		// Keep a record of successor nodes.
		Node* parent;
		// Used to view the search in reverse at the end.
		Node* child;

		float g; // Cost of this and it's predecessors.
		float h; // Heuristic estimate of the distance of the goal.
		float f; // Sum of cost and heuristic.

		Node(UserState userState) : parent(0), child(0), g(0.0f), h(0.0f), f(0.0), _userState(userState) {}

		UserState _userState;
	};

	// Compare the f values of the two nodes.
	class HeapCompare_f {
	public:
		bool operator()(const Node* x, const Node* y) const {
			return x->f > y->f;
		}
	};

public:
	AStarSearch(void) :
			_state(SEARCH_STATE_NOT_INITIALIZED),
			_currentSolutionNode(NULL),
			_allocateNodeCount(0),
			_cancelRequest(false) {}

	~AStarSearch(void) {}

	int GetState(void)				{ return _state; }

	// Cancel the search and free up the memory. -- This can be called at any time.
	void CancelSearch(void)		{ _cancelRequest = true; }

	// Set the start/goal state.
	void SetStartAndGoalStates(UserState& start, UserState& goal) {
		_cancelRequest= false;

		_start = AllocateNode(start);
		_goal  = AllocateNode(goal);

		assert((_start != NULL && _goal != NULL));

		_state = SEARCH_STATE_SEARCHING;

		// Initialize the AStar specific parts of the start node.
		// You only need to fill out the state information.
		_start->g = 0;
		_start->h = _start->_userState.GoalDistanceEstimate(_goal->_userState);
		_start->f = _start->g + _start->h;
		_start->parent = 0;

		// Push the start node onto the open list.
		_openList.push_back(_start); // Heap is now unsorted.

		// Sort back element into the heap.
		push_heap(_openList.begin(), _openList.end(), HeapCompare_f());

		// Initialize counter for the search steps.
		_steps = 0;
	}

	// Search one step.
	unsigned int SearchStep(void) {
		// Break if the search has not been initialized.
		assert((_state > SEARCH_STATE_NOT_INITIALIZED) && ( _state < SEARCH_STATE_INVALID));

		// Ensure it is safe to do a seach step once the seach has succeeded.
		if((_state == SEARCH_STATE_SUCCEEDED) || (_state == SEARCH_STATE_FAILED)) { return false; }

		if(_openList.empty() || _cancelRequest) {
			// Then there is nothing left to search, so fail.
			FreeAllNodes();
			_state = SEARCH_STATE_FAILED;
			return _state;
		}

		_steps++;

		// Pop the best node. -- The one with the lowest f.
		Node* n = _openList.front(); // Get pointer to the node.
		pop_heap(_openList.begin(), _openList.end(), HeapCompare_f());
		_openList.pop_back();

		// Check for the goal, once we pop that, we are done.
		if(n->_userState.IsGoal(_goal->_userState)) {
			// Copy the parent pointer of n, as we will use the passed in goal node.
			_goal->parent = n->parent;

			// If the goal was passed in at the start..
			if(false == n->_userState.IsSameState(_start->_userState)) {
				FreeNode(n);

				// Set the child pointers in each node, apart from goal, as it has no child.
				Node* nodeChild = _goal;
				Node* nodeParent = _goal->parent;

				while(nodeChild != _start) {
					// Start is always the first node by definition.
					nodeParent->child = nodeChild;

					nodeChild = nodeParent;
					nodeParent = nodeParent->parent;
				}
			}
			// Delete nodes that are not needed for the solution.
			FreeUnusedNodes();
			_state = SEARCH_STATE_SUCCEEDED;

			return _state;
		} else {
			// Not goal.

			/*
			 * Generate the successors of this node.
			 * The user helps us to do this, and we keep
			 * the new nodes in _successors.
			 */
			_successors.clear(); // empty the vector of successor nodes to n.

			// The user provides this functions and uses AddSuccessor to add each
			// successor of node 'n' to _successors.
			bool ret = n->_userState.GetSuccessors(this, n->parent ? &n->parent->_userState : NULL);

			if(!ret) {
				typename vector<Node*>::iterator successor;

				// Free the nodes that may have previously been added.
				for(successor = _successors.begin(); successor != _successors.end(); successor++) {
					FreeNode((*successor));
				}
				// Empty vector of successor nodes nodes to n.
				_successors.clear();

				// Free up everything else we allocated along the way.
				FreeAllNodes();

				_state = SEARCH_STATE_OUT_OF_MEMORY;
				return _state;
			}
			// Now handle each successor to the current node..
			for(typename vector<Node*>::iterator successor = _successors.begin(); successor != _successors.end(); successor++) {
				// The g value for this successor.
				float newg = n->g + n->_userState.GetCost((*successor)->_userState);

				/*
				 * We need to see whether the node is on the open or closed
				 * list. If it is, but the node that is already on them is better
				 * (lower g) then we can forget about this successor.
				 *
				 * First linear search of open list to find node.
				 */
				typename vector<Node*>::iterator openlist_result;
				for(openlist_result = _openList.begin(); openlist_result != _openList.end(); openlist_result++) {
					if((*openlist_result)->_userState.IsSameState((*successor)->_userState)) {
						break;
					}
				}
				if(openlist_result != _openList.end()) {
					// We found this state open.
					if((*openlist_result)->g <= newg) {
						FreeNode((*successor));
						// The one on the open list is cheaper than this one.
						continue;
					}
				}
				typename vector<Node*>::iterator closedlist_result;
				for(closedlist_result = _closedList.begin(); closedlist_result != _closedList.end(); closedlist_result++) {
					if((*closedlist_result)->_userState.IsSameState((*successor)->_userState)) {
						break;
					}
				}
				if(closedlist_result != _closedList.end()) {
					// We found this state closed.
					if((*closedlist_result)->g <= newg) {
						// The one on the closed list is cheaper than this one.
						FreeNode((*successor));
						continue;
					}
				}
				// This node is the best node so fat with this particular state.
				// So lets keep it, and set up its AStar specific data..
				(*successor)->parent = n;
				(*successor)->g = newg;
				(*successor)->h = (*successor)->_userState.GoalDistanceEstimate(_goal->_userState);
				(*successor)->f = (*successor)->g + (*successor)->h;

				// Remove successor from closed if it was on it.
				if(closedlist_result != _closedList.end()) {
					// Remove it from the closed list.
					FreeNode((*closedlist_result));
					_closedList.erase(closedlist_result);

					// Now remake the heap!!
					make_heap(_openList.begin(), _openList.end(), HeapCompare_f());
				}

				// The heap is now unsorted.
				_openList.push_back((*successor));

				// Sort back elements into the heap.
				push_heap(_openList.begin(), _openList.end(), HeapCompare_f());
			}
			// push n onto the closed list as it has now been expanded.
			_closedList.push_back(n);
		} // (Not goal, so expand)
		return _state; // Succeeded bool should be false at this point.
	}

	// Call this to add a successor to a list of
	// successors when expanding the seach frontier.
	bool AddSuccessor(UserState& state) {
		Node* node = AllocateNode(state);

		if(node) {
			node->_userState = state;
			_successors.push_back(node);
			return true;
		}
		return false;
	}

	// Free the solution nodes.
	// This is done to clean up all used nodes in memory when you are
	// done with the search.
	void FreeSolutionNodes(void) {
		Node* n = _start;

		if(_start->child) {
			while(n != _goal) {
				Node* del = n;
				n = n->child;
				FreeNode(del);

				del = NULL;
			}
			FreeNode(n); // Delete the goal.
		} else {
			// If the start node is the solution, we need to just
			// delete the start goal nodes.
			FreeNode(_start);
			FreeNode(_goal);
		}
	}

	// -- Some methods for travelling through the solution. --

	// Get the start node.
	UserState* GetSolutionStart(void) {
		_currentSolutionNode = _start;
		if(_start) {
			return &_start->_userState;
		} else {
			return NULL;
		}
	}

	// Get the next node.
	UserState* GetSolutionNext(void) {
		if(_currentSolutionNode) {
			if(_currentSolutionNode->child) {
				Node* child = _currentSolutionNode->child;
				_currentSolutionNode = _currentSolutionNode->child;

				return &child->_userState;
			}
		}

		return NULL;
	}

	// Get the end node.
	UserState* GetSolutionEnd(void) {
		_currentSolutionNode = _goal;
		if(_goal) {
			return &_goal->_userState;
		} else {
			return NULL;
		}
	}

	// Step through the solution backwards.
	UserState* GetSolutionPrev(void) {
		if(_currentSolutionNode) {
			if(_currentSolutionNode->parent) {
				Node* parent = _currentSolutionNode->parent;

				_currentSolutionNode = _currentSolutionNode->parent;

				return &parent->_userState;
			}
		}

		return NULL;
	}

	// It will be useful to be able to view the open
	// and closed lists at each step for debugging.
	UserState* GetOpenListStart(void) {
		float f, g, h;
		return GetOpenListStart(f, g, h);
	}

	UserState* GetOpenListStart(float& f, float& g, float& h) {
		iterDbgOpen = _openList.begin();
		if(iterDbgOpen != _openList.end()) {
			f = (*iterDbgOpen)->f;
			g = (*iterDbgOpen)->g;
			h = (*iterDbgOpen)->h;
			return &(*iterDbgOpen)->_userState;
		}

		return NULL;
	}

	UserState* GetOpenListNext(void) {
		float f, g, h;
		return GetOpenListNext(f, g, h);
	}

	UserState* GetOpenListNext(float& f, float& g, float& h) {
		iterDbgOpen++;
		if(iterDbgOpen != _openList.end()) {
			f = (*iterDbgOpen)->f;
			g = (*iterDbgOpen)->g;
			h = (*iterDbgOpen)->h;
			return &(*iterDbgOpen)->_userState;
		}

		return NULL;
	}

	// Closes states.
	UserState* GetClosedListStart(void) {
		float f, g, h;
		return GetClosedListStart(f, g, h);
	}

	UserState* GetClosedListStart(float& f, float& g, float& h) {
		iterDbgClosed = _closedList.begin();
		if(iterDbgClosed != _closedList.begin()) {
			f = (*iterDbgClosed)->f;
			g = (*iterDbgClosed)->g;
			h = (*iterDbgClosed)->h;
			return &(iterDbgClosed)->_userState;
		}

		return NULL;
	}

	UserState* GetClosedListNext(void) {
		float f, g, h;
		return GetClosedListNext(f, g, h);
	}

	UserState* GetClosedListNext(float& f, float& g, float& h) {
		iterDbgClosed++;
		if(iterDbgClosed != _closedList.end()) {
			f = (*iterDbgClosed)->f;
			g = (*iterDbgClosed)->g;
			h = (*iterDbgClosed)->h;
			return &(*iterDbgClosed)->_userState;
		}

		return NULL;
	}

	// Get the number of steps.
	int GetStepCount(void)		{return _steps; }

private:
	// Called when a search fails or is cancelled to free up all unused memory.
	void FreeAllNodes(void) {
		// Iterate the open list and delete all nodes.
		typename vector<Node*>::iterator iterOpen = _openList.begin();

		while(iterOpen != _openList.end()) {
			Node* n = (*iterOpen);
			FreeNode(n);

			iterOpen++;
		}

		_openList.clear();

		// Iterate closed list and delete unused nodes.
		typename vector<Node*>::iterator iterClosed;

		for(iterClosed = _closedList.begin(); iterClosed != _closedList.end(); iterClosed++) {
			Node* n = (*iterClosed);
			FreeNode(n);
		}

		_closedList.clear();

		// Delete the goal.
		FreeNode(_goal);
	}

	/*
	 * Called when the search ends. A lot of nodes may
	 * be created that are still present when the search
	 * ends. They will be deleted with this method.
	 */
	void FreeUnusedNodes(void) {
		// Iterate open list and delete unused nodes.
		typename vector<Node*>::iterator iterOpen = _openList.begin();

		while(iterOpen != _openList.end()) {
			Node *n = (*iterOpen);

			if(!n->child) {
				FreeNode(n);
				n = NULL;
			}

			iterOpen++;
		}

		_openList.clear();

		// Iterate closed list and delete all unused nodes.
		typename vector<Node*>::iterator iterClosed;

		for(iterClosed = _closedList.begin(); iterClosed != _closedList.end(); iterClosed++) {
			Node *n = (*iterClosed);

			if(!n->child) {
				FreeNode(n);
				n = NULL;
			}
		}

		_closedList.clear();

	}

	Node* AllocateNode(UserState& userState) {
		Node *p = new Node(userState);
		return p;
	}

	void FreeNode(Node* node) {
		_allocateNodeCount--;
		delete node;
	}

	// Data.
private:
	// Heap.
	vector<Node*> _openList;
	vector<Node*> _closedList;
	vector<Node*> _successors;

	// State.
	unsigned int  _state;

	// Count steps.
	int _steps;

	// Start/Goal state pointers.
	Node* _start;
	Node* _goal;

	Node* _currentSolutionNode;

	// Debug
	typename vector<Node*>::iterator iterDbgOpen;
	typename vector<Node*>::iterator iterDbgClosed;

	// Count memory allocations and free.
	int _allocateNodeCount;

	bool _cancelRequest;
};
