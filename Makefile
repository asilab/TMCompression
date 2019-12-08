.PHONY: all clean

CXX = g++ -std=c++14
CXXFLAGS = -Wall -Wextra -O3 -m64 -g
LFLAGS = -pthread

objects = src/tmId.o \
		  src/turingMachine.o \
 		  src/metrics.o \
		  src/markovTable.o \
		  src/parseArgs.o \
		  src/util.o \
		  src/tm.o \
		  src/NormalizedCompressionMarkovTable.o \
		  src/randomString.o \
		  src/stateMatrixParser.o \
		  src/main.o

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

tm: $(objects)
	$(CXX) $(LFLAGS) $^ -o $@

all: tm

clean:
	rm -f src/*.o tm

# Dependencies

main.o: src/main.cpp src/tm.h src/parseArgs.h

src/tmId.o: src/tmId.h src/tmId.cpp

src/metrics.o: src/metrics.cpp src/metrics.h src/turingMachine.h

src/randomString.o: src/randomString.cpp src/randomString.h

src/tm.o: src/tm.cpp src/tm.h src/turingMachine.h src/markovTable.h src/util.h src/NormalizedCompressionMarkovTable.h

src/markovTable.o: src/markovTable.cpp src/markovTable.h src/turingMachine.h src/util.h src/metrics.h

src/NormalizedCompressionMarkovTable.o: src/NormalizedCompressionMarkovTable.h src/markovTable.h src/metrics.h

src/parseArgs.o: src/parseArgs.cpp src/parseArgs.h src/traversal.h src/util.h

src/turingMachine.o: src/turingMachine.cpp src/turingMachine.h src/traversal.h src/tmId.h

src/util.o: src/util.cpp src/util.h

src/stateMatrixParser.o: src/stateMatrixParser.cpp src/stateMatrixParser.h src/turingMachine.h

ioStNormalize: src/ioStNormalize.cpp
	g++ -std=c++14 -o ioStNormalize src/ioStNormalize.cpp src/tmId.h

ioAverage: src/ioAverage.cpp
	g++ -std=c++14 -o ioAverage src/ioAverage.cpp 

ioGrowthAverage: src/ioGrowthAverage.cpp
	g++ -std=c++14 -o ioGrowthAverage src/ioGrowthAverage.cpp

TMsimulator: val/TMsimulator.c 
	g++ -o TMsimulator val/TMsimulator.c -lgmpxx -lgmp