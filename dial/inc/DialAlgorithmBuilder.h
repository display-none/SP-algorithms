/*
 * Shortest Path Algorithms - Dial's Algorithm
 *      Author: Jacek Ho³a
 */

#ifndef DIALALGORITHMBUILDER_H_
#define DIALALGORITHMBUILDER_H_

#include "AlgorithmBuilder.h"
#include "BucketSkipList.h"
#include "GraphStructures.h"
#include "DialAlgorithm.h"

class DialAlgorithmBuilder: public AlgorithmBuilder<DialAlgorithm> {
	private:
		BucketSkipList* bucketsList;
	public:

		void withStartNode(long startNodeId);
		void withNodes(long nodesCount);

		DialAlgorithm* build();
};

void DialAlgorithmBuilder::withStartNode(long startNodeId) {
	AlgorithmBuilder<DialAlgorithm>::withStartNode(startNodeId);
	bucketsList = new BucketSkipList(maxCost);
	bucketsList->insertNode(nodesList->getNode(startNodeId));
}

void DialAlgorithmBuilder::withNodes(long nodesCount) {
	AlgorithmBuilder<DialAlgorithm>::withNodes(nodesCount);
}

DialAlgorithm* DialAlgorithmBuilder::build() {
	return new DialAlgorithm(getNodes(), bucketsList, destinationNodeId);
}


#endif /* DIALALGORITHMBUILDER_H_ */
