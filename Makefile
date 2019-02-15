.PHONY: all clean

CXX = g++ -std=c++14
CXXFLAGS = -Wall -Wextra -O3 -m64 -g

objects = src/turingMachine.o \
		  src/markovTable.o \
		  src/parseArgs.o \
		  src/main.o

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

tm: $(objects)
	$(CXX) $^ -o $@

all: tm

clean:
	rm -f src/*.o tm

# Dependencies

main.o: src/main.cpp src/turingMachine.h src/markovTable.h src/parseArgs.h

src/markovTable.o: src/markovTable.cpp src/markovTable.h src/turingMachine.h

src/parseArgs.o: src/parseArgs.cpp src/parseArgs.h

src/turingMachine.o: src/turingMachine.cpp src/turingMachine.h
