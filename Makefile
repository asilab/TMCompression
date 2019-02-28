.PHONY: all clean

CXX = g++ -std=c++14
CXXFLAGS = -Wall -Wextra -O3 -m64 -g
LFLAGS = -pthread

objects = src/turingMachine.o \
		  src/markovTable.o \
		  src/parseArgs.o \
		  src/util.o \
		  src/tm.o \
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

src/tm.o: src/tm.cpp src/tm.h src/turingMachine.h src/markovTable.h src/util.h

src/markovTable.o: src/markovTable.cpp src/markovTable.h src/turingMachine.h src/util.h

src/parseArgs.o: src/parseArgs.cpp src/parseArgs.h src/traversal.h src/util.h

src/turingMachine.o: src/turingMachine.cpp src/turingMachine.h src/traversal.h

src/util.o: src/util.cpp src/util.h

ioNormalize: src/ioNormalize.cpp
	 g++ -std=c++14 -o ioNormalize src/ioNormalize.cpp