/*
 * Shortest Path Algorithms - Dijkstra's Algorithm
 *      Author: Jacek Ho³a
 */

#include "DijkstraAlgorithm.h"

DijkstraAlgorithm::DijkstraAlgorithm(NodeListElement* nodes, long destinationNodeId) {
	this->nodesToVisit = new NodeListElement();		//first element is a dummy
	this->nodesVisited = new NodeListElement();		//first element is a dummy
	this->nodesToVisit->next = nodes;
	this->destinationNodeId = destinationNodeId;
	this->verbose = false;
}

DijkstraAlgorithm::~DijkstraAlgorithm() {

	NodeListElement* currentListElement = this->nodesVisited->next;
	NodeListElement* toDelete;
	while(currentListElement != NULL) {
		deleteNode(currentListElement->node);
		toDelete = currentListElement;
		currentListElement = currentListElement->next;
		delete toDelete;
	}

	delete this->nodesToVisit;
	delete this->nodesVisited;
}

inline void DijkstraAlgorithm::deleteNode(Node* node) {
	NodeAdjacency* current = node->adjacency;
	NodeAdjacency* toDelete;
	while(current != NULL) {
		toDelete = current;
		current = current->next;
		delete toDelete;
	}
	delete node;
}

void DijkstraAlgorithm::printResult() {
	NodeListElement* currentListElement = this->nodesVisited->next;
	while(currentListElement->next != NULL) {
		cout << "node " << currentListElement->node->id << ": min cost=" <<
				currentListElement->node->minCost << ", predecessor=" << currentListElement->node->predecessor->id << endl;
		currentListElement = currentListElement->next;
	}
}

void inline DijkstraAlgorithm::resetNodeState(long newStartNodeId, NodeListElement* currentListElement) {
	if (currentListElement->node->id == newStartNodeId) {
		currentListElement->node->state = fringe;
		currentListElement->node->minCost = 0;
		currentListElement->node->predecessor = NULL;
	} else {
		currentListElement->node->state = initial;
		currentListElement->node->minCost = LONG_MAX;
	}
}

void DijkstraAlgorithm::resetState(long newStartNodeId, long newDestinationNodeId) {
	//set new destination
	destinationNodeId = newDestinationNodeId;

	//go to the end of nodes to visit
	NodeListElement* currentListElement = this->nodesToVisit;
	while(currentListElement->next != NULL) {
		currentListElement = currentListElement->next;
	}

	//put visited nodes there
	currentListElement->next = this->nodesVisited->next;
	this->nodesVisited->next = NULL;

	//reset all nodes
	currentListElement = this->nodesToVisit->next;
	while(currentListElement != NULL) {
		resetNodeState(newStartNodeId, currentListElement);
		currentListElement = currentListElement->next;
	}
}

bool inline DijkstraAlgorithm::existNotVisitedNodes() {
	return this->nodesToVisit->next != NULL;
}

Node* DijkstraAlgorithm::extractMinCostNodeAndRemoveItFromList() {
	NodeListElement* minCostPredecessor = NULL;
	long minCost = LONG_MAX;

	NodeListElement* currentPredecessor = this->nodesToVisit;
	while(currentPredecessor->next != NULL) {
		if(currentPredecessor->next->node->state == fringe) {
			if(currentPredecessor->next->node->minCost < minCost) {
				minCostPredecessor = currentPredecessor;
				minCost = currentPredecessor->next->node->minCost;
			}
		}
		currentPredecessor = currentPredecessor->next;
	}

	if(minCostPredecessor == NULL) {
		throw InvalidDataException("Error: cannot reach all nodes from specified start node");
	}

	//moving the min distance node to visited nodes list
	NodeListElement* minCostElement = minCostPredecessor->next;
	minCostPredecessor->next = minCostElement->next;
	minCostElement->next = this->nodesVisited->next;
	this->nodesVisited->next = minCostElement;

	return minCostElement->node;
}

void inline DijkstraAlgorithm::updateNeighborsOfNode(Node* node) {
	NodeAdjacency* currentNeighbor = node->adjacency;
	while(currentNeighbor != NULL) {
		if(currentNeighbor->node->state != seen) {
			updateNeighbor(node, currentNeighbor->node, currentNeighbor->cost);
		}
		currentNeighbor = currentNeighbor->next;
	}
}

void inline DijkstraAlgorithm::updateNeighbor(Node* node, Node* neighbor, long cost) {
	if(node->minCost + cost < neighbor->minCost) {
		neighbor->minCost = node->minCost + cost;
		neighbor->predecessor = node;
	}
	neighbor->state = fringe;
}

/**
 * returns cost of path from source to destination if destination available, 0 otherwise
 */
long DijkstraAlgorithm::execute() {

	while(existNotVisitedNodes()) {
		Node* minCostNode = extractMinCostNodeAndRemoveItFromList();

		if(minCostNode->id == destinationNodeId) return minCostNode->minCost;
		updateNeighborsOfNode(minCostNode);
	}

	if(verbose) {
		printResult();
	}
	return 0;
}

void DijkstraAlgorithm::setVerbose(bool verbose) {
	this->verbose = verbose;
}
