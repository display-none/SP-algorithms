/*
 * Shortest Path Algorithms - Dial's Algorithm
 *      Author: Jacek Ho³a
 */

#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <ctime>

#include "DialAlgorithm.h"
#include "DialAlgorithmBuilder.h"
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

	ParsingHelper<DialAlgorithm>* helper;
	DialAlgorithmBuilder* algorithmBuilder;
	DialAlgorithm* algorithm;

	double totalTime;
	int executions;

	inline void executeAlgorithm(DialAlgorithm* algorithm);
};

#endif
