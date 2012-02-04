#include "Pathfinding.h"

template<class UserState>
AStarSearch<UserState>::AStarSearch(void) :
		_state(SEARCH_STATE_NOT_INITIALIZED),
		_currentSolutionNode(NULL),
		_allocateNodeCount(0),
		_cancelRequest(false) {}

template<class UserState>
AStarSearch<UserState>::~AStarSearch(void) {

}

template<class UserState>
void AStarSearch<UserState>::SetStartAndGoalStates(UserState& start, UserState& goal) {
	_cancelRequest= false;

	_start = AllocateNode();
	_goal  = AllocateNode();

	assert((_start != NULL && _goal != NULL));

	_start->_userState = _start;
	_goal->_userState  = _goal;

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

template<class UserState>
unsigned int  AStarSearch<UserState>::SearchStep(void) {
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

template<class UserState>
bool AStarSearch<UserState>::AddSuccessor(UserState& state) {

}

template<class UserState>
void AStarSearch<UserState>::FreeSolutionNodes(void) {

}

template<class UserState>
UserState* AStarSearch<UserState>::GetSolutionStart(void) {

}

template<class UserState>
UserState* AStarSearch<UserState>::GetSolutionNext(void) {

}

template<class UserState>
UserState* AStarSearch<UserState>::GetSolutionEnd(void) {

}

template<class UserState>
UserState* AStarSearch<UserState>::GetSolutionPrev(void) {

}

template<class UserState>
UserState* AStarSearch<UserState>::GetOpenListStart(void) {

}

template<class UserState>
UserState* AStarSearch<UserState>::GetOpenListStart(float& f, float& g, float& h) {

}

template<class UserState>
UserState* AStarSearch<UserState>::GetOpenListNext(void) {

}

template<class UserState>
UserState* AStarSearch<UserState>::GetOpenListNext(float& f, float& g, float& h) {

}

template<class UserState>
UserState* AStarSearch<UserState>::GetClosedListStart(void) {

}

template<class UserState>
UserState* AStarSearch<UserState>::GetClosedListStart(float& f, float& g, float& h) {

}

template<class UserState>
UserState* AStarSearch<UserState>::GetClosedListNext(void) {

}

template<class UserState>
UserState* AStarSearch<UserState>::GetClosedListNext(float& f, float& g, float& h) {

}

// Private.
template<class UserState>
void AStarSearch<UserState>::FreeAllNodes(void) {

}

template<class UserState>
void AStarSearch<UserState>::FreeUnusedNodes(void) {

}

template<class UserState>
typename AStarSearch<UserState>::Node* AStarSearch<UserState>::AllocateNode(void) {

}

template<class UserState>
void AStarSearch<UserState>::FreeNode(Node* node) {

}
