/*
 * Shortest Path Algorithms - common
 *      Author: Jacek Ho³a
 */

#ifndef ALGORITHMFACTORY_H_
#define ALGORITHMFACTORY_H_

#include "GraphStructures.h"
#include "NodeSkipList.h"
#include <cstdlib>

template <typename T>	//T should be a derivative of Algorithm, but it seems this is not possible in C++
class AlgorithmBuilder {
	protected:
		NodeSkipList* nodesList;
		long destinationNodeId;
		long maxCost;
	public:
		virtual ~AlgorithmBuilder();

		virtual void withNodes(long nodesCount);
		virtual void withArc(long fromNodeId, long toNodeId, long distance);
		virtual void withStartNode(long startNodeId);
		virtual void withDestinationNode(long destinationNodeId);
		virtual void withMaxCost(long maxCost);

		NodeListElement* getNodes();
		virtual T* build() = 0;
};

template<typename T>
AlgorithmBuilder<T>::~AlgorithmBuilder() {
	delete nodesList;
}

template<typename T>
void AlgorithmBuilder<T>::withNodes(long nodesCount) {
	nodesList = new NodeSkipList(nodesCount);
}

template<typename T>
void AlgorithmBuilder<T>::withArc(long fromNodeId, long toNodeId, long cost) {
	Node* fromNode = nodesList->getNode(fromNodeId);
	fromNode->adjacency = new NodeAdjacency(nodesList->getNode(toNodeId), cost, fromNode->adjacency);
}

template<typename T>
void AlgorithmBuilder<T>::withStartNode(long startNodeId) {
	Node* startNode = nodesList->getNode(startNodeId);
	startNode->minCost = 0;
	startNode->predecessor = NULL;
	startNode->state = fringe;
}

template<typename T>
void AlgorithmBuilder<T>::withDestinationNode(long destinationNodeId) {
	this->destinationNodeId = destinationNodeId;
}

template<typename T>
void AlgorithmBuilder<T>::withMaxCost(long maxCost) {
	this->maxCost = maxCost;
}

template<typename T>
NodeListElement* AlgorithmBuilder<T>::getNodes() {
	return nodesList->getNodes();
}

#endif /* ALGORITHMFACTORY_H_ */
