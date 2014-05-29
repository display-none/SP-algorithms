/*
 * Shortest Path Algorithms - Radix Heap Algorithm
 *      Author: Jacek Ho³a
 */

#include "RadixHeap.h"

RadixHeap::RadixHeap() {
	lastRemovedCost = 0;
	currentNumberOfNodes = 0;
	buckets = new NodeListElement*[heapSize];
	for(int i = 0; i < heapSize; i++) {
		buckets[i] = new NodeListElement();			//initialize with dummy elements so that removing can be done without silly checks
	}
}

RadixHeap::~RadixHeap() {
	NodeListElement* nodeElement;
	NodeListElement* toDelete;
	for(int i = 0; i < heapSize; i++) {
		nodeElement = buckets[i];
		while(nodeElement != NULL) {
			toDelete = nodeElement;
			nodeElement = nodeElement->next;
			delete toDelete;
		}
	}
}

void RadixHeap::reset() {
	NodeListElement* nodeElement;
	NodeListElement* toDelete;
	for(int i = 0; i < heapSize; i++) {
		nodeElement = buckets[i]->next;
		while(nodeElement != NULL) {
			toDelete = nodeElement;
			nodeElement = nodeElement->next;
			delete toDelete;
		}
		buckets[i]->next = NULL;
	}

	lastRemovedCost = 0;
	currentNumberOfNodes = 0;
}

bool RadixHeap::hasAnyNodes() {
	return currentNumberOfNodes > 0;
}

void RadixHeap::insertNode(Node* node) {
	NodeListElement* newNodeElement = new NodeListElement();
	newNodeElement->node = node;
	node->holdingElement = newNodeElement;
	insertNodeElement(newNodeElement);
	currentNumberOfNodes++;
}

void RadixHeap::insertNodeElement(NodeListElement* nodeElement) {
	long bucketNumber = getFirstDifferentBitPosition(nodeElement->node->minCost);

	nodeElement->prev = buckets[bucketNumber];
	nodeElement->next = buckets[bucketNumber]->next;
	if(nodeElement->next != NULL) nodeElement->next->prev = nodeElement;
	buckets[bucketNumber]->next = nodeElement;
}

void RadixHeap::moveNodeToProperBucket(Node* node, long oldCost) {
	if(getFirstDifferentBitPosition(oldCost) ==
			getFirstDifferentBitPosition(node->minCost)) {
		return;
	}

	NodeListElement* holdingElement = node->holdingElement;
	holdingElement->prev->next = holdingElement->next;
	if(holdingElement->next != NULL) holdingElement->next->prev = holdingElement->prev;

	insertNodeElement(holdingElement);
}

/*
 * Returns one plus the index of the most significant bit where idToCheck and lastRemovedCost differ,
 * or if they are equal, returns zero.
 */
inline long RadixHeap::getFirstDifferentBitPosition(long idToCheck) {
	long xored = idToCheck xor lastRemovedCost;
	if(xored == 0) return 0;
 	return (8 * sizeof(unsigned long)) - __builtin_clzl(xored);
}

//#include <intrin.h>
//
//#pragma intrinsic(_BitScanReverse)
//
//inline long RadixHeap::getFirstDifferentBitPosition(long idToCheck) {
//	long xored = idToCheck ^ lastRemovedCost;
//	unsigned long xoredUnsigned = xored;
//	unsigned long position;
// 	_BitScanReverse(&position, xoredUnsigned);
//	return position + 1;
//}

Node* RadixHeap::getMinCostNode() {
	NodeListElement* bucket = getFirstNonEmptyBucket();
	NodeListElement* minElement = removeMinimalElementFromBucket(bucket);

	if(minElement->node->minCost != lastRemovedCost) {
		lastRemovedCost = minElement->node->minCost;

		NodeListElement* currentElement = bucket->next;
		NodeListElement* elementToMove;
		while(currentElement != NULL) {
			elementToMove = currentElement;
			currentElement = currentElement->next;
			insertNodeElement(elementToMove);
		}
		bucket->next = NULL;
	}

	currentNumberOfNodes--;
	Node* nodeToReturn = minElement->node;
	delete minElement;
	return nodeToReturn;
}

inline NodeListElement* RadixHeap::getFirstNonEmptyBucket() {
	for(int i = 0; i < heapSize; i++) {
		if(buckets[i]->next != NULL) {
			return buckets[i];
		}
	}
	cout << "Fuck, didn't find nonempty bucket" << endl;
	exit(69);
}

inline NodeListElement* RadixHeap::removeMinimalElementFromBucket(NodeListElement* bucket) {
	NodeListElement* currentElement = bucket->next;
	NodeListElement* minElement = currentElement;
	while(currentElement != NULL) {
		if(currentElement->node->minCost < minElement->node->minCost) {
			minElement = currentElement;
		}
		currentElement = currentElement->next;
	}

	minElement->prev->next = minElement->next;
	if(minElement->next != NULL) minElement->next->prev = minElement->prev;

	return minElement;
}
