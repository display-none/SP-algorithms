/*
 * Shortest Path Algorithms - Dijkstra's Algorithm
 *      Author: Jacek Ho³a
 */

#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <ctime>

#include "DijkstraAlgorithm.h"
#include "DijkstraAlgorithmBuilder.h"
#include "ParsingHelper.h"
#include "InvalidDataException.h"

using namespace std;


class Main {
public:
	Main(int argc, char** argv);
	~Main();

	void run();

private:
	int argc;
	char** argv;

	ParsingHelper<DijkstraAlgorithm>* helper;
	DijkstraAlgorithmBuilder* algorithmBuilder;
	DijkstraAlgorithm* algorithm;

	double totalTime;
	int executions;

	inline void executeAlgorithm(DijkstraAlgorithm* algorithm);
};

#endif
