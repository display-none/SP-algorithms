/*
 * Shortest Path Algorithms - common
 *      Author: Jacek Ho³a
 */

#include "BucketSkipList.h"


BucketSkipList::BucketSkipList(long maxCost) {
	int pointersArraySize = (int) sqrt((double)maxCost);
	pointers = new BucketListElement*[pointersArraySize];

	leapSize = floor(((double)maxCost / pointersArraySize) + 1);

	offset = 0;
	currentMinCost = 0;
	listSize = maxCost + 1;
	currentNumberOfNodes = 0;

	buckets = new BucketListElement();
	pointers[0] = buckets;
	BucketListElement* lastElement = this->buckets;
	for(long i = 1; i <= maxCost; i++) {
		lastElement->next = new BucketListElement();
		lastElement = lastElement->next;

		if(i % leapSize == 0) {
			pointers[i / leapSize] = lastElement;
		}
	}
	lastElement->next = pointers[0];
}

void BucketSkipList::reset() {
	if(currentNumberOfNodes != 0) {
		BucketListElement* currentBucket = buckets;
		for(int i = 0; i <= listSize; i++) {
			if(currentBucket->nodes != NULL) {
				NodeListElement* nodeElement = currentBucket->nodes;
				NodeListElement* toDelete;
				while(nodeElement != NULL) {
					toDelete = nodeElement;
					nodeElement = nodeElement->next;
					delete toDelete;
				}
				currentBucket->nodes = NULL;
			}
			currentBucket = currentBucket->next;
		}
	}
	currentMinCost = 0;
	offset = 0;
}

bool BucketSkipList::hasAnyNodes() {
	return currentNumberOfNodes > 0;
}

Node* BucketSkipList::getMinCostNode() {
	NodeListElement* minCostNodeElement;

	BucketListElement* firstBucket = getBucket(currentMinCost);
	if(firstBucket->nodes == NULL) {
		long distanceToNextEmptyBucket = 1;
		BucketListElement* currentBucket = firstBucket->next;
		while(currentBucket->nodes == NULL) {
			distanceToNextEmptyBucket++;
			currentBucket = currentBucket->next;
		}

		currentMinCost += distanceToNextEmptyBucket;
		offset = (offset + distanceToNextEmptyBucket) % listSize;

		minCostNodeElement = currentBucket->nodes;
		currentBucket->nodes = minCostNodeElement->next;
	} else {
		minCostNodeElement = firstBucket->nodes;
		firstBucket->nodes = minCostNodeElement->next;
	}

	Node* minCostNode = minCostNodeElement->node;
	delete minCostNodeElement;
	currentNumberOfNodes--;
	return minCostNode;
}

BucketSkipList::~BucketSkipList() {
	BucketListElement* toDelete;
	BucketListElement* lastElement = pointers[0]->next;
	pointers[0]->next = NULL;
	while(lastElement != NULL) {
		NodeListElement* nodeElement = lastElement->nodes;
		NodeListElement* nodeToDelete;
		while(nodeElement != NULL) {
			nodeToDelete = nodeElement;
			nodeElement = nodeElement->next;
			delete nodeToDelete;
		}

		toDelete = lastElement;
		lastElement = lastElement->next;
		delete toDelete;
	}
	delete[] pointers;
}

void BucketSkipList::insertNode(Node* node) {
	NodeListElement* newNodeElement = new NodeListElement();
	newNodeElement->node = node;
	insertNode(newNodeElement);
	currentNumberOfNodes++;
}

void BucketSkipList::insertNode(NodeListElement* nodeListElement) {
	BucketListElement* bucket = getBucket(nodeListElement->node->minCost);
	nodeListElement->next = bucket->nodes;
	bucket->nodes = nodeListElement;
}

void BucketSkipList::moveNodeToProperBucket(long nodeId, long oldCost) {
	BucketListElement* bucket = getBucket(oldCost);
	NodeListElement* foundNodeElement = NULL;
	if(bucket->nodes->node->id == nodeId) {
		foundNodeElement = bucket->nodes;
		bucket->nodes = foundNodeElement->next;
	} else {
		NodeListElement* lastElement = bucket->nodes;
		while(lastElement->next != NULL) {
			if(lastElement->next->node->id == nodeId) {
				foundNodeElement = lastElement->next;
				lastElement->next = foundNodeElement->next;
				break;
			}
			lastElement = lastElement->next;
		}
	}

	if(foundNodeElement == NULL) {
		cout << "Fuck. Haven't found the node" << endl;
		exit(69);
	}

	insertNode(foundNodeElement);
}

BucketListElement* BucketSkipList::getBucket(long cost) {
	long bucketNumber = cost - currentMinCost;			//right now this list stores buckets from currentMinCost to currentMinCost + C
	long bucketNumberShifted = (bucketNumber + offset) % listSize;	//but bucket are shifted by offset, so
																	//we have to take that into account when accessing the array
	BucketListElement* lastElement = pointers[bucketNumberShifted / leapSize];
	for(long i = leapSize * (bucketNumberShifted / leapSize); i < bucketNumberShifted; i++) {
		lastElement = lastElement->next;
	}
	return lastElement;
}
