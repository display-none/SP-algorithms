/*
 * Shortest Path Algorithms - Radix Heap Algorithm
 *      Author: Jacek Ho³a
 */

#include "RadixHeapAlgorithm.h"

RadixHeapAlgorithm::RadixHeapAlgorithm(NodeListElement* nodes, RadixHeap* radixHeap, long destinationNodeId) {
	this->nodes = nodes;
	this->radixHeap = radixHeap;
	this->destinationNodeId = destinationNodeId;
	this->verbose = false;
}

RadixHeapAlgorithm::~RadixHeapAlgorithm() {
	
	delete radixHeap;

	NodeListElement* currentListElement = this->nodes;
	NodeListElement* toDelete;
	while(currentListElement != NULL) {
		deleteNode(currentListElement->node);
		toDelete = currentListElement;
		currentListElement = currentListElement->next;
		delete toDelete;
	}

}

inline void RadixHeapAlgorithm::deleteNode(Node* node) {
	NodeAdjacency* current = node->adjacency;
	NodeAdjacency* toDelete;
	while(current != NULL) {
		toDelete = current;
		current = current->next;
		delete toDelete;
	}
	delete node;
}

void RadixHeapAlgorithm::printResult() {
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

void inline RadixHeapAlgorithm::resetNodeState(long newStartNodeId, NodeListElement* currentListElement) {
	if (currentListElement->node->id == newStartNodeId) {
		currentListElement->node->state = initial;
		currentListElement->node->minCost = 0;
		currentListElement->node->predecessor = NULL;
		radixHeap->insertNode(currentListElement->node);
	} else {
		currentListElement->node->state = initial;
		currentListElement->node->minCost = LONG_MAX;
	}
}

void RadixHeapAlgorithm::resetState(long newStartNodeId, long newDestinationNodeId) {
	//set new destination
	destinationNodeId = newDestinationNodeId;

	//reset radixHeap
	radixHeap->reset();

	//reset all nodes
	NodeListElement* currentListElement = this->nodes;
	while(currentListElement != NULL) {
		resetNodeState(newStartNodeId, currentListElement);
		currentListElement = currentListElement->next;
	}
}

void inline RadixHeapAlgorithm::updateNeighborsOfNode(Node* node) {
	NodeAdjacency* currentNeighbor = node->adjacency;
	while(currentNeighbor != NULL) {
		if(currentNeighbor->node->state != seen) {
			updateNeighbor(node, currentNeighbor->node, currentNeighbor->cost);
		}
		currentNeighbor = currentNeighbor->next;
	}
}

void inline RadixHeapAlgorithm::updateNeighbor(Node* node, Node* neighbor, long cost) {
	if(node->minCost + cost < neighbor->minCost) {
		long oldCost = neighbor->minCost;
		neighbor->minCost = node->minCost + cost;
		neighbor->predecessor = node;

		if(neighbor->state == initial) {
			radixHeap->insertNode(neighbor);
		} else {
			radixHeap->moveNodeToProperBucket(neighbor, oldCost);
		}
		neighbor->state = fringe;
	}
}

/**
 * returns cost of path from source to destination if destination available, 0 otherwise
 */
long RadixHeapAlgorithm::execute() {

	while(radixHeap->hasAnyNodes()) {
		Node* minCostNode = radixHeap->getMinCostNode();

		int* a = new int();
		int* b = new int();
		int* c = new int();
		int* d = new int();
		int* e = new int();

		delete a;
		delete b;
		delete c;
		delete d;
		delete e;

		if(minCostNode->id == destinationNodeId) return minCostNode->minCost;
		updateNeighborsOfNode(minCostNode);
		minCostNode->state = seen;
	}

	if(verbose) {
		printResult();
	}
	return 0;
}

void RadixHeapAlgorithm::setVerbose(bool verbose) {
	this->verbose = verbose;
}
