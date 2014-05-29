/*
 * Shortest Path Algorithms - common
 *      Author: Jacek Ho³a
 */

#ifndef GRAPHSTRUCTURES_H_
#define GRAPHSTRUCTURES_H_

#include "settings.h"
#include <cstdlib>
#include <climits>

enum NodeState {
	initial, fringe, seen
};

struct NodeAdjacency;
struct NodeListElement;

/* ###### */
/*  Node  */
/* ###### */

#ifdef ___GRAPH_ALTERNATIVE___

struct Node {
	long id;
	long minCost;
	NodeState state;
	Node* predecessor;
	NodeAdjacency* adjacency;
	NodeListElement* holdingElement;

	Node(long id) : id(id), minCost(LONG_MAX), state(initial), predecessor(NULL), adjacency(NULL), holdingElement(NULL) {
	}
	~Node() { };
private:
	Node(const Node&);
	Node& operator=(const Node&);
};

#else

struct Node {
	long id;
	long minCost;
	NodeState state;
	Node* predecessor;
	NodeAdjacency* adjacency;

	Node(long id) : id(id), minCost(LONG_MAX), state(initial), predecessor(NULL), adjacency(NULL) {
	}
	~Node() { };
private:
	Node(const Node&);
	Node& operator=(const Node&);
};

#endif

/* ############### */
/*  NodeAdjacency  */
/* ############### */


struct NodeAdjacency {
	Node* node;
	long cost;
	NodeAdjacency* next;

	NodeAdjacency(Node* node, long cost, NodeAdjacency* next) : node(node), cost(cost), next(next) {
	}
	~NodeAdjacency() { };
private:
	NodeAdjacency(const NodeAdjacency&);
	NodeAdjacency& operator=(const NodeAdjacency&);
};

/* ################# */
/*  NodeListElement  */
/* ################# */

#ifdef ___GRAPH_ALTERNATIVE___

struct NodeListElement {
	Node* node;
	NodeListElement* next;
	NodeListElement* prev;
	NodeListElement(): node(NULL), next(NULL), prev(NULL) { }
private:
	NodeListElement(const NodeListElement&);
	NodeListElement& operator=(const NodeListElement&);
};

#else

struct NodeListElement {
	Node* node;
	NodeListElement* next;
	NodeListElement(): node(NULL), next(NULL) { }
private:
	NodeListElement(const NodeListElement&);
	NodeListElement& operator=(const NodeListElement&);
};

#endif

/* ################### */
/*  BucketListElement  */
/* ################### */


struct BucketListElement {
	NodeListElement* nodes;
	BucketListElement* next;
	BucketListElement(): nodes(NULL), next(NULL) { }
private:
	BucketListElement(const BucketListElement&);
	BucketListElement& operator=(const BucketListElement&);
};


#endif /* GRAPHSTRUCTURES_H_ */
