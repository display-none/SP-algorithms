/*
 * Shortest Path Algorithms - Radix Heap Algorithm
 *      Author: Jacek Ho³a
 */

#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <ctime>

#include "RadixHeapAlgorithm.h"
#include "RadixHeapAlgorithmBuilder.h"
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

	ParsingHelper<RadixHeapAlgorithm>* helper;
	RadixHeapAlgorithmBuilder* algorithmBuilder;
	RadixHeapAlgorithm* algorithm;

	double totalTime;
	int executions;

	inline void executeAlgorithm(RadixHeapAlgorithm* algorithm);
};

#endif
