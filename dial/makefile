CC=gcc
CCFLAGS = -Wall -pedantic -I ./inc/ -I ./../common/inc -Ofast -lstdc++ -std=c++11
all: Dial

Dial: ./src/main.cpp ./inc/main.h ./tmp/DialAlgorithm.o ./inc/DialAlgorithmBuilder.h ./tmp/InvalidDataException.o \
	./../common/inc/ParsingHelper.h ./tmp/NodeSkipList.o ./tmp/BucketSkipList.o
	$(CC) ./src/main.cpp ./tmp/DialAlgorithm.o ./tmp/InvalidDataException.o ./tmp/NodeSkipList.o ./tmp/BucketSkipList.o $(CCFLAGS) -o ./bin/dial

./tmp/DialAlgorithm.o: ./src/DialAlgorithm.cpp ./inc/DialAlgorithm.h ./../common/inc/Algorithm.h ./../common/inc/GraphStructures.h \
	./../common/inc/InvalidDataException.h ./../common/inc/BucketSkipList.h
	$(CC) $(CCFLAGS) -c ./src/DialAlgorithm.cpp -o $@

./inc/DialAlgorithmBuilder.h: ./inc/DialAlgorithm.h ./../common/inc/AlgorithmBuilder.h ./../common/inc/GraphStructures.h ./../common/inc/BucketSkipList.h

./../common/inc/AlgorithmBuilder.h: ./../common/inc/GraphStructures.h ./tmp/NodeSkipList.o

./../common/inc/GraphStructures.h:  ./inc/settings.h

./tmp/InvalidDataException.o: ./../common/src/InvalidDataException.cpp ./../common/inc/InvalidDataException.h
	$(CC) $(CCFLAGS) -c ./../common/src/InvalidDataException.cpp -o $@
	
./../common/inc/ParsingHelper.h: ./../common/inc/AlgorithmBuilder.h \
	./../common/inc/ErrorCodes.h
	
./tmp/NodeSkipList.o: ./../common/src/NodeSkipList.cpp ./../common/inc/NodeSkipList.h
	$(CC) $(CCFLAGS) -c ./../common/src/NodeSkipList.cpp -o $@
	
./tmp/BucketSkipList.o: ./../common/src/BucketSkipList.cpp ./../common/inc/BucketSkipList.h ./../common/inc/GraphStructures.h
	$(CC) $(CCFLAGS) -c ./../common/src/BucketSkipList.cpp -o $@


clean: 
	rm -f ./tmp/DialAlgorithm.o ./tmp/DialAlgorithmBuilder.o ./tmp/InvalidDataException.o ./tmp/NodeSkipList.o ./tmp/BucketSkipList.o ./tmp/*~
