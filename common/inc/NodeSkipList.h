/*
 * Shortest Path Algorithms - common
 *      Author: Jacek Ho³a
 */

#ifndef NODESKIPLIST_H_
#define NODESKIPLIST_H_

#include "GraphStructures.h"

#include <cmath>

/**
 * Skip list implementation to store Nodes.
 * Will be using one level with sqrt(n) pointers stored in an array for speed of access.
 *
 * Algorithms are responsible for freeing the memory allocated for nodes
 */

class NodeSkipList {
private:
	NodeListElement* nodes;
	NodeListElement** pointers;
	long leapSize;
public:
	NodeSkipList(long nodesCount);
	~NodeSkipList();

	Node* getNode(long index);

	NodeListElement* getNodes();

private:
	NodeSkipList(const NodeSkipList&);
	NodeSkipList& operator=(const NodeSkipList&);
};

#endif /* NODESKIPLIST_H_ */
