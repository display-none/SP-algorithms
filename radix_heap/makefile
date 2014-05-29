CC=gcc
CCFLAGS = -Wall -pedantic -I ./inc/ -I ./../common/inc -Ofast -lstdc++ -std=c++11
all: RadixHeap

RadixHeap: ./src/main.cpp ./inc/main.h ./tmp/RadixHeapAlgorithm.o ./inc/RadixHeapAlgorithmBuilder.h ./tmp/InvalidDataException.o \
	./../common/inc/ParsingHelper.h ./tmp/NodeSkipList.o ./tmp/RadixHeap.o
	$(CC) ./src/main.cpp ./tmp/RadixHeapAlgorithm.o ./tmp/InvalidDataException.o ./tmp/NodeSkipList.o ./tmp/RadixHeap.o $(CCFLAGS) -o ./bin/radixHeap

./tmp/RadixHeapAlgorithm.o: ./src/RadixHeapAlgorithm.cpp ./inc/RadixHeapAlgorithm.h ./../common/inc/Algorithm.h ./../common/inc/GraphStructures.h \
	./../common/inc/InvalidDataException.h ./inc/RadixHeap.h
	$(CC) $(CCFLAGS) -c ./src/RadixHeapAlgorithm.cpp -o $@

./inc/RadixHeapAlgorithmBuilder.h: ./inc/RadixHeapAlgorithm.h ./../common/inc/AlgorithmBuilder.h ./../common/inc/GraphStructures.h ./inc/RadixHeap.h

./../common/inc/AlgorithmBuilder.h: ./../common/inc/GraphStructures.h ./tmp/NodeSkipList.o

./../common/inc/GraphStructures.h:  ./inc/settings.h
	
./tmp/InvalidDataException.o: ./../common/src/InvalidDataException.cpp ./../common/inc/InvalidDataException.h
	$(CC) $(CCFLAGS) -c ./../common/src/InvalidDataException.cpp -o $@
	
./../common/inc/ParsingHelper.h: ./../common/inc/AlgorithmBuilder.h ./../common/inc/ErrorCodes.h
	
./tmp/NodeSkipList.o: ./../common/src/NodeSkipList.cpp ./../common/inc/NodeSkipList.h
	$(CC) $(CCFLAGS) -c ./../common/src/NodeSkipList.cpp -o $@
	
./tmp/RadixHeap.o: ./src/RadixHeap.cpp ./inc/RadixHeap.h ./../common/inc/GraphStructures.h
	$(CC) $(CCFLAGS) -c ./src/RadixHeap.cpp -o $@

clean: 
	rm -f ./tmp/RadixHeapAlgorithm.o ./tmp/RadixHeapAlgorithmBuilder.o ./tmp/InvalidDataException.o ./tmp/NodeSkipList.o ./tmp/RadixHeap.o ./tmp/*~
