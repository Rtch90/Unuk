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
		SEARCH_STATE_NOT_INITIALISED,
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

		Node(void) : parent(0), child(0), g(0.0f), h(0.0f), f(0.0) {}

		UserState _UserState;
	};

	// Compare the f values of the two nodes.
	class HeapCompare_f {
	public:
		bool operator()(const Node* x, const Node* y) const {
			return x->f > y->f;
		}
	};

public:
	AStarSearch(void);
	~AStarSearch(void);

	int GetState(void)				{ return _state; }

	// Cancel the search and free up the memory. -- This can be called at any time.
	void CancelSearch(void)		{ _cancelRequest = true; }

	// Set the start/goal state.
	void SetStartAndGoalStates(UserState& start, UserState& goal);

	// Search one step.
	unsigned int SearchStep(void);

	// Call this to add a successor to a list of
	// successors when expanding the seach frontier.
	bool AddSuccessor(UserState& state);

	// Free the solution nodes.
	// This is done to clean up all used nodes in memory when you are
	// done with the search.
	void FreeSolutionNodes(void);

	// -- Some methods for travelling through the solution. --

	// Get the start node.
	UserState* GetSolutionStart(void);

	// Get the next node.
	UserState* GetSolutionNext(void);

	// Get the end node.
	UserState* GetSolutionEnd(void);

	// Step through the solution backwards.
	UserState* GetSolutionPrev(void);

	// It will be useful to be able to view the open
	// and closed lists at each step for debugging.
	UserState* GetOpenListStart(void);
	UserState* GetOpenListStart(float& f, float& g, float& h);
	UserState* GetOpenListNext(void);
	UserState* GetOpenListNext(float& f, float& g, float& h);

	// Closes states.
	UserState* GetClosedListStart(void);
	UserState* GetClosedListStart(float& f, float& g, float& h);
	UserState* GetClosedListNext(void);
	UserState* GetClosedListNext(float& f, float& g, float& h);

	// Get the number of steps.
	int GetStepCount(void)		{return _steps; }

private:
	// Called when a search fails or is cancelled to free up all unused memory.
	void FreeAllNodes(void);

	/*
	 * Called when the search ends. A lot of nodes may
	 * be created that are still present when the search
	 * ends. They will be deleted with this method.
	 */
	void FreeUnusedNodes(void);

	Node* AllocateNode(void);

	void FreeNode(Node* node);

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
