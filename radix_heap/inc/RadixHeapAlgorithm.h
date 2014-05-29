/*
 * Shortest Path Algorithms - Radix Heap Algorithm
 *      Author: Jacek Ho³a
 */

#ifndef RADIXHEAPALGORITHM_H_
#define RADIXHEAPALGORITHM_H_

#include "Algorithm.h"
#include "RadixHeap.h"
#include "GraphStructures.h"
#include "InvalidDataException.h"
#include <cstdlib>
#include <climits>
#include <iostream>

using namespace std;

class RadixHeapAlgorithm: public Algorithm {
		NodeListElement* nodes;
		RadixHeap* radixHeap;
		long destinationNodeId;
		bool verbose;

	public:
		RadixHeapAlgorithm(NodeListElement* nodes, RadixHeap* radixHeap, long destinationNodeId);
		virtual ~RadixHeapAlgorithm();

		long execute();
		void printResult();

		void resetState(long newStartNodeId, long newDestinationNodeId);
		void setVerbose(bool verbose);

	private:
		inline void deleteNode(Node* node);

		bool inline existNotVisitedNodes();
		Node* extractMinCostNodeAndRemoveItFromList();
		void inline updateNeighborsOfNode(Node* node);
		void inline updateNeighbor(Node* node, Node* neighbor, long distance);
		void inline resetNodeState(long newStartNodeId, NodeListElement* currentListElement);
};

#endif /* RADIXHEAPALGORITHM_H_ */
