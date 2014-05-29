/*
 * Shortest Path Algorithms - Dijkstra's Algorithm
 *      Author: Jacek Ho³a
 */

#include "main.h"

inline void Main::executeAlgorithm(DijkstraAlgorithm* algorithm) {
	try {
		const clock_t beginTime = clock();
		long result = algorithm->execute();
		const clock_t endTime = clock();
		double execTime = (double)(endTime - beginTime) / CLOCKS_PER_SEC * 1000;

		totalTime += execTime;
		executions++;
		cout << "cpu time elapsed: " << execTime << " milliseconds" << endl;

		helper->updateOutputWithNewResult(result);
	} catch (InvalidDataException& e) {
		cout << "Algorithm execution failed" << endl;
		cout << e.getMessage() << endl;
	}
}

Main::Main(int argc, char** argv) : argc(argc), argv(argv) {
	helper = new ParsingHelper<DijkstraAlgorithm>("dijkstra");
	algorithmBuilder = new DijkstraAlgorithmBuilder();
}

Main::~Main() {
	delete helper;
	delete algorithm;
	delete algorithmBuilder;
}

void Main::run() {
	helper->parseOptions(argc, argv);
	algorithm = helper->buildAlgorithm(algorithmBuilder);

	executeAlgorithm(algorithm);

	long newStartNodeId;
	long newDestinationNodeId;
	while(helper->hasNextStartNode()) {
		newStartNodeId = helper->getNextStartNodeId();
		newDestinationNodeId = helper->getNextDestinationNodeId();
		algorithm->resetState(newStartNodeId, newDestinationNodeId);
		executeAlgorithm(algorithm);
	}

	double avgTime = totalTime / executions;
	helper->writeOutputFile(avgTime);
}


int main(int argc, char** argv) {

	Main* main = new Main(argc, argv);
	main->run();
	delete main;

	return 0;
}
