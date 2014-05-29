/*
 * Shortest Path Algorithms - Dial's Algorithm
 *      Author: Jacek Ho³a
 */

#ifndef DIALALGORITHM_H_
#define DIALALGORITHM_H_

#include "Algorithm.h"
#include "BucketSkipList.h"
#include "GraphStructures.h"
#include "InvalidDataException.h"
#include <cstdlib>
#include <climits>
#include <iostream>

using namespace std;

class DialAlgorithm: public Algorithm {
		NodeListElement* nodes;
		BucketSkipList* bucketsList;
		long destinationNodeId;
		bool verbose;

	public:
		DialAlgorithm(NodeListElement* nodes, BucketSkipList* bucketsList, long destinationNodeId);
		virtual ~DialAlgorithm();

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

#endif /* DIALALGORITHM_H_ */
