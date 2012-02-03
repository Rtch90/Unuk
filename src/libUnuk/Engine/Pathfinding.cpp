#include "Pathfinding.h"

template<typename UserState>
AStarSearch<UserState>::AStarSearch(void) :
		_state(SEARCH_STATE_NOT_INITIALISED),
		_currentSolutionNode(NULL),
		_allocateNodeCount(0),
		_cancelRequest(false) {}

template<typename UserState>
AStarSearch<UserState>::~AStarSearch(void) {

}

template<typename UserState>
void AStarSearch<UserState>::SetStartAndGoalStates(UserState& start, UserState& goal) {

}

template<typename UserState>
unsigned int  AStarSearch<UserState>::SearchStep(void) {

}
