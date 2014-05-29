/*
 * Shortest Path Algorithms - Dijkstra's Algorithm
 *      Author: Jacek Ho³a
 */

#ifndef DIJKSTRAALGORITHM_H_
#define DIJKSTRAALGORITHM_H_

#include "Algorithm.h"
#include "GraphStructures.h"
#include "InvalidDataException.h"
#include <cstdlib>
#include <climits>
#include <iostream>

using namespace std;

class DijkstraAlgorithm: public Algorithm {
		NodeListElement* nodesToVisit;
		NodeListElement* nodesVisited;
		long destinationNodeId;
		bool verbose;

	public:
		DijkstraAlgorithm(NodeListElement* nodes, long destinationNodeId);
		virtual ~DijkstraAlgorithm();

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

#endif /* DIJKSTRAALGORITHM_H_ */
