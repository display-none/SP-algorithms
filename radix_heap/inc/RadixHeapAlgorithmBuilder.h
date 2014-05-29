/*
 * Shortest Path Algorithms - Radix Heap Algorithm
 *      Author: Jacek Ho³a
 */

#ifndef RADIXHEAPALGORITHMBUILDER_H_
#define RADIXHEAPALGORITHMBUILDER_H_

#include "AlgorithmBuilder.h"
#include "RadixHeap.h"
#include "GraphStructures.h"
#include "RadixHeapAlgorithm.h"

class RadixHeapAlgorithmBuilder: public AlgorithmBuilder<RadixHeapAlgorithm> {
	private:
		RadixHeap* radixHeap;
	public:
		virtual ~RadixHeapAlgorithmBuilder();

		void withStartNode(long startNodeId);
		void withNodes(long nodesCount);

		RadixHeapAlgorithm* build();
};

RadixHeapAlgorithmBuilder::~RadixHeapAlgorithmBuilder() {

}

void RadixHeapAlgorithmBuilder::withStartNode(long startNodeId) {
	AlgorithmBuilder<RadixHeapAlgorithm>::withStartNode(startNodeId);
	radixHeap = new RadixHeap();
	radixHeap->insertNode(nodesList->getNode(startNodeId));
}

void RadixHeapAlgorithmBuilder::withNodes(long nodesCount) {
	AlgorithmBuilder<RadixHeapAlgorithm>::withNodes(nodesCount);
}

RadixHeapAlgorithm* RadixHeapAlgorithmBuilder::build() {
	return new RadixHeapAlgorithm(getNodes(), radixHeap, destinationNodeId);
}


#endif /* RADIXHEAPALGORITHMBUILDER_H_ */
