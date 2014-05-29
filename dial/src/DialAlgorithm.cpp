/*
 * Shortest Path Algorithms - Dial's Algorithm
 *      Author: Jacek Ho³a
 */

#include "DialAlgorithm.h"

DialAlgorithm::DialAlgorithm(NodeListElement* nodes, BucketSkipList* bucketsList, long destinationNodeId) {
	this->nodes = nodes;
	this->bucketsList = bucketsList;
	this->destinationNodeId = destinationNodeId;
	this->verbose = false;
}

DialAlgorithm::~DialAlgorithm() {

	NodeListElement* currentListElement = this->nodes;
	NodeListElement* toDelete;
	while(currentListElement != NULL) {
		deleteNode(currentListElement->node);
		toDelete = currentListElement;
		currentListElement = currentListElement->next;
		delete toDelete;
	}

	delete bucketsList;
}

inline void DialAlgorithm::deleteNode(Node* node) {
	NodeAdjacency* current = node->adjacency;
	NodeAdjacency* toDelete;
	while(current != NULL) {
		toDelete = current;
		current = current->next;
		delete toDelete;
	}
	delete node;
}

void DialAlgorithm::printResult() {
	NodeListElement* currentListElement = this->nodes;
	while(currentListElement != NULL) {
		cout << "node " << currentListElement->node->id;
		if(currentListElement->node->minCost != LONG_MAX) {
			cout << ": min cost=" << currentListElement->node->minCost;

			if(currentListElement->node->predecessor != NULL) {
				cout << ", predecessor=" << currentListElement->node->predecessor->id << endl;
			} else {
				cout << ", start node" << endl;
			}
		} else {
			cout << ": not reachable" << endl;
		}
		currentListElement = currentListElement->next;
	}
}

void inline DialAlgorithm::resetNodeState(long newStartNodeId, NodeListElement* currentListElement) {
	if (currentListElement->node->id == newStartNodeId) {
		currentListElement->node->state = initial;
		currentListElement->node->minCost = 0;
		currentListElement->node->predecessor = NULL;
		bucketsList->insertNode(currentListElement->node);
	} else {
		currentListElement->node->state = initial;
		currentListElement->node->minCost = LONG_MAX;
	}
}

void DialAlgorithm::resetState(long newStartNodeId, long newDestinationNodeId) {
	//set new destination
	destinationNodeId = newDestinationNodeId;

	//reset buckets list
	bucketsList->reset();

	//reset all nodes
	NodeListElement* currentListElement = this->nodes;
	while(currentListElement != NULL) {
		resetNodeState(newStartNodeId, currentListElement);
		currentListElement = currentListElement->next;
	}
}

void inline DialAlgorithm::updateNeighborsOfNode(Node* node) {
	NodeAdjacency* currentNeighbor = node->adjacency;
	while(currentNeighbor != NULL) {
		if(currentNeighbor->node->state != seen) {
			updateNeighbor(node, currentNeighbor->node, currentNeighbor->cost);
		}
		currentNeighbor = currentNeighbor->next;
	}
}

void inline DialAlgorithm::updateNeighbor(Node* node, Node* neighbor, long cost) {
	if(node->minCost + cost < neighbor->minCost) {
		long oldCost = neighbor->minCost;
		neighbor->minCost = node->minCost + cost;
		neighbor->predecessor = node;

		if(neighbor->state == initial) {
			bucketsList->insertNode(neighbor);
		} else {
			bucketsList->moveNodeToProperBucket(neighbor->id, oldCost);
		}
		neighbor->state = fringe;
	}
}

/**
 * returns cost of path from source to destination if destination available, 0 otherwise
 */
long DialAlgorithm::execute() {

	while(bucketsList->hasAnyNodes()) {
		Node* minCostNode = bucketsList->getMinCostNode();

		if(minCostNode->id == destinationNodeId) return minCostNode->minCost;
		updateNeighborsOfNode(minCostNode);
		minCostNode->state = seen;
	}

	if(verbose) {
		printResult();
	}
	return 0;
}

void DialAlgorithm::setVerbose(bool verbose) {
	this->verbose = verbose;
}
