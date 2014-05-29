/*
 * Shortest Path Algorithms - common
 *      Author: Jacek Ho³a
 */

#include "NodeSkipList.h"


NodeSkipList::NodeSkipList(long nodesCount) {
	int pointersArraySize = (int) sqrt((double)nodesCount);
	pointers = new NodeListElement*[pointersArraySize];

	leapSize = floor(((double)nodesCount / pointersArraySize) + 1);

	nodes = new NodeListElement();
	pointers[0] = nodes;
	NodeListElement* lastElement = this->nodes;
	lastElement->node = new Node(1);
	for(long i = 2; i <= nodesCount; i++) {
		lastElement->next = new NodeListElement();
		lastElement->next->node = new Node(i);
		lastElement = lastElement->next;

		if(i % leapSize == 0) {
			pointers[i / leapSize] = lastElement;
		}
	}
	lastElement->next = NULL;
}

NodeSkipList::~NodeSkipList() {
	delete[] pointers;
}

Node* NodeSkipList::getNode(long index) {
	NodeListElement* lastElement = pointers[index / leapSize];
	for(long i = lastElement->node->id; i < index; i++) {
		lastElement = lastElement->next;
	}
	return lastElement->node;
}


NodeListElement* NodeSkipList::getNodes() {
	return nodes;
}
