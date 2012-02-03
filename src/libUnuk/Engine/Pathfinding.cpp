#include "Pathfinding.h"

template<class UserState>
AStarSearch<UserState>::AStarSearch(void) :
		_state(SEARCH_STATE_NOT_INITIALISED),
		_currentSolutionNode(NULL),
		_allocateNodeCount(0),
		_cancelRequest(false) {}

template<class UserState>
AStarSearch<UserState>::~AStarSearch(void) {

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
