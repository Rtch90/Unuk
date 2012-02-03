#include "Pathfinding.h"

template<class UserState>
AStarSearch<UserState>::AStarSearch(void) :
		_state(SEARCH_STATE_NOT_INITIALISED),
		_currentSolutionNode(NULL),
		_allocateNodeCount(0),
		_cancelRequest(false) {}

template<class UserState>
AStarSearch<UserState>::~AStarSearch(void) {
	_cancelRequest= false;

	_start = AllocateNode();
	_goal  = AllocateNode();

	assert((_start != NULL && _goal != NULL));

	_start->_UserState = _start;
	_goal->_UserState  = _goal;

	_state = SEARCH_STATE_SEARCHING;

	// Initialise the AStar specific parts of the start node.
	// You only need to fill out the state information.
	_start->g = 0;
	_start->h = _start->_UserState.GoalDistanceEstimate(_goal->_UserState);
	_start->f = _start->g + _start->h;
	_start->parent = 0;

	// Push the start node onto the open list.
	_openList.push_back(_start); // Heap is now unsorted.

	// Sort back element into the heap.
	push_heap(_openList.begin(), _openList.end(), HeapCompare_f());

	// Initialise counter for the search steps.
	_steps = 0;
}

template<class UserState>
void AStarSearch<UserState>::SetStartAndGoalStates(UserState& start, UserState& goal) {

}

template<class UserState>
unsigned int  AStarSearch<UserState>::SearchStep(void) {

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
