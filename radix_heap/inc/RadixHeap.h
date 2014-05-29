/*
 * Shortest Path Algorithms - Radix Heap Algorithm
 *      Author: Jacek Ho³a
 */

#ifndef RADIXHEAP_H_
#define RADIXHEAP_H_

#include "GraphStructures.h"

#include <iostream>

using namespace std;

class RadixHeap {
	private:
		static const int heapSize = 8 * sizeof(long) + 1;		//bit size of long plus one for 0 bucket
		long lastRemovedCost;
		long currentNumberOfNodes;
		NodeListElement** buckets;
	public:
		RadixHeap();
		~RadixHeap();

		bool hasAnyNodes();

		Node* getMinCostNode();

		void insertNode(Node* node);
		void moveNodeToProperBucket(Node* node, long oldCost);

		void reset();
	private:
		void insertNodeElement(NodeListElement* nodeElement);

		inline long getFirstDifferentBitPosition(long idToCheck);
		inline NodeListElement* getFirstNonEmptyBucket();
		inline NodeListElement* removeMinimalElementFromBucket(NodeListElement* bucket);
};



#endif /* RADIXHEAP_H_ */
