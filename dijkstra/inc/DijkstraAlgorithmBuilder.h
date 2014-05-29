/*
 * Shortest Path Algorithms - Dijkstra's Algorithm
 *      Author: Jacek Ho³a
 */

#ifndef DIJKSTRAALGORITHMBUILDER_H_
#define DIJKSTRAALGORITHMBUILDER_H_

#include "AlgorithmBuilder.h"
#include "GraphStructures.h"
#include "DijkstraAlgorithm.h"

class DijkstraAlgorithmBuilder: public AlgorithmBuilder<DijkstraAlgorithm> {
	public:
		virtual ~DijkstraAlgorithmBuilder();
		DijkstraAlgorithm* build();
};

DijkstraAlgorithmBuilder::~DijkstraAlgorithmBuilder() {

}

DijkstraAlgorithm* DijkstraAlgorithmBuilder::build() {
	return new DijkstraAlgorithm(getNodes(), destinationNodeId);
}


#endif /* DIJKSTRAALGORITHMBUILDER_H_ */
