/*
 * Shortest Path Algorithms - common
 *      Author: Jacek Ho³a
 */

#ifndef PARSINGHELPER_H_
#define PARSINGHELPER_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include <climits>
#include "AlgorithmBuilder.h"
#include "ErrorCodes.h"

using namespace std;

template<typename T>
class ParsingHelper {
	public:
		ParsingHelper(string algorithmName);

		void parseOptions(int argc, char** argv);
		void printHelp();

		bool hasNextStartNode();
		long getNextStartNodeId();
		long getNextDestinationNodeId();

		void updateOutputWithNewResult(long cost);
		void writeOutputFile(double avgTime);

		T* buildAlgorithm(AlgorithmBuilder<T>* algorithmBuilder);
	private:
		string dataFilename;
		string sourcesFilename;
		string sourcesOutputFilename;
		string pairsFilename;
		string pairsOutputFilename;
		bool verbose;

		long minCost;
		long maxCost;
		long arcsLeftToSpecify;

		string algorithmName;
		stringstream output;

		long* sources;		//an array keeping ids of sources, sources[0] is reserved and indicates place of next source id to insert
							//while parsing and next source id to return while executing algorithm
		long* destinations;	//same here, but used for pairs

		AlgorithmBuilder<T>* algorithmBuilder;

		bool areRequiredArgumentsSet();
		void parseFile(string filename, void (ParsingHelper<T>::*parsingFunction)(ifstream&));
		void inline checkForString(ifstream& ss, string pattern, string filename);

		void parseDataFile();
		inline void parseDataFileLine(ifstream& stream);
		inline void parseDataFileProblem(ifstream& stream);
		inline void parseDataFileArc(ifstream& stream);
		inline void assertAllArcsSpecified();

		void parseSourceFile();
		inline void parseSourceFileLine(ifstream& stream);
		inline void parseSourceFileProblem(ifstream& stream);
		inline void parseSourceFileSource(ifstream& stream);

		void parsePairFile();
		inline void parsePairFileLine(ifstream& stream);
		inline void parsePairFileProblem(ifstream& stream);
		inline void parsePairFilePair(ifstream& stream);

		inline void assertAtLeastOneStartNode();

		void writeOutputFileForSources(double avgTime);
		void writeOutputFileForPairs();
};

template<typename T>
ParsingHelper<T>::ParsingHelper(string algorithmName) {
	this->algorithmName = algorithmName;
	minCost = LONG_MAX;
	maxCost = 0;
	destinations = NULL;
	verbose = false;
}

template<typename T>
void ParsingHelper<T>::printHelp() {
	cout << "usage: " << endl;
	cout << algorithmName << " -d dataFile.gr -ss sources.ss -oss output.ss.res [-v]" << endl;
	cout << "	-d dataFile.gr		specifies a file with data" << endl;
	cout << "	-ss sources.ss		specifies a file with sources" << endl;
	cout << "	-oss output.ss.res	specifies an output file" << endl;
	cout << "	-v					enables verbose mode" << endl;
	cout << endl << "OR" << endl;
	cout << algorithmName << " -d dataFile.gr -p2p pair.p2p -op2p output.p2p.res [-v]" << endl;
	cout << "	-d dataFile.gr			specifies a file with data" << endl;
	cout << "	-p2p pair.p2p			specifies a file with pairs of source and destination" << endl;
	cout << "	-op2p output.p2p.res	specifies an output file" << endl;
	cout << "	-v						enables verbose mode" << endl << endl;
	cout << "Error codes:" << endl;
	cout << "	0 - success" << endl;
	cout << "	" << ERR_WRONG_OPTIONS << " - wrong options" << endl;
	cout << "	" << ERR_CANNOT_OPEN_FILE << " - cannot open file" << endl;
	cout << "	" << ERR_SYNTAX << " - wrong syntax in one of given files" << endl;

	exit(ERR_WRONG_OPTIONS);
}

template<typename T>
bool ParsingHelper<T>::areRequiredArgumentsSet() {
	return 	(dataFilename != "" && sourcesOutputFilename != "" && sourcesFilename != ""
				&& pairsOutputFilename == "" && pairsFilename == "")
			|| (dataFilename != "" && sourcesOutputFilename == "" && sourcesFilename == ""
					&& pairsOutputFilename != "" && pairsFilename != "");
}

template<typename T>
void ParsingHelper<T>::parseOptions(int argc, char** argv) {
	for(int i = 1; i < argc; i++) {
		string arg = string(argv[i]);
		if(arg == "-d") {
			dataFilename = string(argv[++i]);
		} else if(arg == "-ss") {
			sourcesFilename = string(argv[++i]);
		} else if(arg == "-oss") {
			sourcesOutputFilename = string(argv[++i]);
		} else if(arg == "-p2p") {
			pairsFilename = string(argv[++i]);
		} else if(arg == "-op2p") {
			pairsOutputFilename = string(argv[++i]);
		} else if(arg == "-v") {
			verbose = true;
		} else {
			cout << "incorrect option: " << arg << endl;
			printHelp();
			break;
		}
	}
	if(!areRequiredArgumentsSet()) {
		cout << "required options in one of available configurations are missing or extra arguments are specified" << endl;
		printHelp();
	}
}

template<typename T>
bool ParsingHelper<T>::hasNextStartNode() {
	return sources[0] != 0;
}

template<typename T>
long ParsingHelper<T>::getNextStartNodeId() {
	if(!hasNextStartNode()) {
		cout << "dupa, cos nie tak" << endl;
		exit(69);
	}
	return sources[sources[0]--];
}

template<typename T>
long ParsingHelper<T>::getNextDestinationNodeId() {
	return destinations == NULL ? -1L : destinations[destinations[0]--];
}

template<typename T>
void ParsingHelper<T>::parseFile(string filename, void (ParsingHelper<T>::*parsingFunction)(ifstream&)) {
	ifstream file (filename);
	if (file.is_open()) {
		while(file.good()) {
			(this->*parsingFunction)(file);
		}
		file.close();
	} else {
		cout << "Unable to open file " << filename << endl;
		exit(ERR_CANNOT_OPEN_FILE);
	}
}

template<typename T>
void inline ParsingHelper<T>::checkForString(ifstream& ss, string pattern, string filename) {
	string substring;
	ss >> substring;
	if(substring != pattern) {
		cout << "Error in file " << filename << ": problem line should contain string '" << pattern << "'" << endl;
		exit(ERR_SYNTAX);
	}
}

/* ################# */
/* DATA FILE PARSING */
/* ################# */

template<typename T>
void ParsingHelper<T>::parseDataFile() {
	parseFile(dataFilename, &ParsingHelper<T>::parseDataFileLine);
	assertAllArcsSpecified();
	output << minCost << " " << maxCost << endl;
}

template<typename T>
inline void ParsingHelper<T>::parseDataFileLine(ifstream& stream) {
	char first;
	if(stream >> first) {		//could encounter EOF
		switch(first) {
			case 'c': {
				//it's a comment, skip
				string str;
				getline(stream, str);
				break;
			}
			case 'p':
				parseDataFileProblem(stream);
				break;
			case 'a':
				parseDataFileArc(stream);
				break;
			default:
				cout << "Error reading file " << dataFilename << " : invalid line specifier: " << first << endl;
				exit(ERR_SYNTAX);
		}
	}
}

template<typename T>
inline void ParsingHelper<T>::parseDataFileProblem(ifstream& stream) {
	//it's a problem specification, should contain string "sp", number of nodes and number of arcs
	long nodesCount;

	checkForString(stream, "sp", dataFilename);

	stream >> nodesCount;
	stream >> arcsLeftToSpecify;

	algorithmBuilder->withNodes(nodesCount);

	output << "f " << dataFilename << " " << sourcesFilename << endl;
	output << "g " << nodesCount << " " << arcsLeftToSpecify << " ";
}

template<typename T>
inline void ParsingHelper<T>::parseDataFileArc(ifstream& stream) {
	//it's an arc specification so it should contain fromNode, toNode and distance
	long fromNode;
	long toNode;
	long cost;

	stream >> fromNode;
	stream >> toNode;
	stream >> cost;

	algorithmBuilder->withArc(fromNode, toNode, cost);
	arcsLeftToSpecify--;

	if(cost < minCost) minCost = cost;
	if(cost > maxCost) maxCost = cost;
}

template<typename T>
inline void ParsingHelper<T>::assertAllArcsSpecified() {
	if(arcsLeftToSpecify != 0) {
		cout << "Error: wrong number of arcs specified" << endl;
		exit(ERR_SYNTAX);
	}
}

/* #################### */
/* SOURCES FILE PARSING */
/* #################### */

template<typename T>
void ParsingHelper<T>::parseSourceFile() {
	if(sourcesFilename == "") return;
	parseFile(sourcesFilename, &ParsingHelper<T>::parseSourceFileLine);
	assertAtLeastOneStartNode();
}

template<typename T>
inline void ParsingHelper<T>::parseSourceFileLine(ifstream& stream) {
	char first;
	if(stream >> first) {		//could encounter EOF
		switch(first) {
			case 'c': {
				//it's a comment, skip
				string str;
				getline(stream, str);
				break;
			}
			case 'p': {
				parseSourceFileProblem(stream);
				break;
			}
			case 's': {
				parseSourceFileSource(stream);
				break;
			}
			default:
				cout << "Error reading file " << sourcesFilename << " : invalid line specifier: " << first << endl;
				exit(ERR_SYNTAX);
		}
	}
}

template<typename T>
inline void ParsingHelper<T>::parseSourceFileProblem(ifstream& stream) {
	//it's a problem specification, should contain strings "aux", "sp" and "ss" and number of sources
	long sourcesCount;

	checkForString(stream, "aux", sourcesFilename);
	checkForString(stream, "sp", sourcesFilename);
	checkForString(stream, "ss", sourcesFilename);

	stream >> sourcesCount;

	sources = new long[sourcesCount+1];	//extra one for record keeping
	sources[0] = 0;						//will keep the last insertion index
}

template<typename T>
inline void ParsingHelper<T>::parseSourceFileSource(ifstream& stream) {
	//it's a source specification, so it should contain source id
	long sourceId;

	stream >> sourceId;
	sources[++sources[0]] = sourceId;
}

template<typename T>
inline void ParsingHelper<T>::assertAtLeastOneStartNode() {
	if(sources[0] == 0) {
		cout << "Error: at least one starting node must be specified" << endl;
		exit(ERR_SYNTAX);
	}
}


/* ################## */
/* PAIRS FILE PARSING */
/* ################## */

template<typename T>
void ParsingHelper<T>::parsePairFile() {
	if(pairsFilename == "") return;
	parseFile(pairsFilename, &ParsingHelper<T>::parsePairFileLine);
	assertAtLeastOneStartNode();
}

template<typename T>
inline void ParsingHelper<T>::parsePairFileLine(ifstream& stream) {
	char first;
	if(stream >> first) {		//could encounter EOF
		switch(first) {
			case 'c': {
				//it's a comment, skip
				string str;
				getline(stream, str);
				break;
			}
			case 'p': {
				parsePairFileProblem(stream);
				break;
			}
			case 's': {
				parsePairFilePair(stream);
				break;
			}
			default:
				cout << "Error reading file " << pairsFilename << " : invalid line specifier: " << first << endl;
				exit(ERR_SYNTAX);
		}
	}
}

template<typename T>
inline void ParsingHelper<T>::parsePairFileProblem(ifstream& stream) {
	//it's a problem specification, should contain strings "aux", "sp" and "p2p" and number of pairs
	long pairsCount;

	checkForString(stream, "aux", pairsFilename);
	checkForString(stream, "sp", pairsFilename);
	checkForString(stream, "p2p", pairsFilename);

	stream >> pairsCount;

	sources = new long[pairsCount+1];	//extra one for record keeping
	sources[0] = 0;						//will keep the last insertion index
	destinations = new long[pairsCount+1];
	destinations[0] = 0;
}

template<typename T>
inline void ParsingHelper<T>::parsePairFilePair(ifstream& stream) {
	//it's a pair specification, so it should contain source id and destination id
	long sourceId;
	long destinationId;

	stream >> sourceId;
	sources[++sources[0]] = sourceId;
	stream >> destinationId;
	destinations[++destinations[0]] = destinationId;
}

template<typename T>
void ParsingHelper<T>::updateOutputWithNewResult(long cost) {
	if(pairsOutputFilename == "") return;
	output << "d " << sources[sources[0] + 1] << " " << destinations[destinations[0] + 1] << " " << cost << endl;
}

template<typename T>
void ParsingHelper<T>::writeOutputFile(double avgTime) {
	if(sourcesOutputFilename != "") {
		writeOutputFileForSources(avgTime);
	} else {
		writeOutputFileForPairs();
	}
}

template<typename T>
void ParsingHelper<T>::writeOutputFileForSources(double avgTime) {
	output << "t " << avgTime << endl;

	ofstream file (sourcesOutputFilename);
	file << "p res sp ss " << algorithmName << endl;
	file << output.rdbuf();
	file.close();
}

template<typename T>
void ParsingHelper<T>::writeOutputFileForPairs() {
	ofstream file (pairsOutputFilename);
	file << "p res sp p2p " << algorithmName << endl;
	file << output.rdbuf();
	file.close();
}

template<typename T>
T* ParsingHelper<T>::buildAlgorithm(AlgorithmBuilder<T>* algorithmBuilder) {
	this->algorithmBuilder = algorithmBuilder;
	parseDataFile();
	parseSourceFile();
	parsePairFile();

	algorithmBuilder->withMaxCost(maxCost);
	algorithmBuilder->withStartNode(getNextStartNodeId());
	algorithmBuilder->withDestinationNode(getNextDestinationNodeId());
	T* algorithm = algorithmBuilder->build();
	algorithm->setVerbose(verbose);
	return algorithm;
}


#endif /* PARSINGHELPER_H_ */
