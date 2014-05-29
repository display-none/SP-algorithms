CC=gcc
CCFLAGS = -Wall -pedantic -I ./inc/ -I ./../common/inc -Ofast -lstdc++ -std=c++11
all: Dijkstra

Dijkstra: ./src/main.cpp ./inc/main.h ./tmp/DijkstraAlgorithm.o ./inc/DijkstraAlgorithmBuilder.h ./tmp/InvalidDataException.o \
	./../common/inc/ParsingHelper.h ./tmp/NodeSkipList.o
	$(CC) ./src/main.cpp ./tmp/DijkstraAlgorithm.o ./tmp/InvalidDataException.o ./tmp/NodeSkipList.o $(CCFLAGS) -o ./bin/dijkstra

./tmp/DijkstraAlgorithm.o: ./src/DijkstraAlgorithm.cpp ./inc/DijkstraAlgorithm.h ./../common/inc/Algorithm.h ./../common/inc/GraphStructures.h \
	./../common/inc/InvalidDataException.h
	$(CC) $(CCFLAGS) -c ./src/DijkstraAlgorithm.cpp -o $@

./inc/DijkstraAlgorithmBuilder.h: ./inc/DijkstraAlgorithm.h ./../common/inc/AlgorithmBuilder.h ./../common/inc/GraphStructures.h

./../common/inc/AlgorithmBuilder.h: ./../common/inc/GraphStructures.h ./tmp/NodeSkipList.o
	
./tmp/InvalidDataException.o: ./../common/src/InvalidDataException.cpp ./../common/inc/InvalidDataException.h
	$(CC) $(CCFLAGS) -c ./../common/src/InvalidDataException.cpp -o $@
	
./../common/inc/ParsingHelper.h: ./../common/inc/AlgorithmBuilder.h \
	./../common/inc/ErrorCodes.h
	
./tmp/NodeSkipList.o: ./../common/src/NodeSkipList.cpp ./../common/inc/NodeSkipList.h
	$(CC) $(CCFLAGS) -c ./../common/src/NodeSkipList.cpp -o $@
	

clean: 
	rm -f ./tmp/DijkstraAlgorithm.o ./tmp/DijkstraAlgorithmBuilder.o ./tmp/InvalidDataException.o ./tmp/NodeSkipList.o ./tmp/*~
