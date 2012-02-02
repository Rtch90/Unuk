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

};
