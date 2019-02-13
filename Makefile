.cpp .o:
	g++ -std=c++14 -c -Wall -Wextra -g $^ -o $@

tm:	    src/turingMachine.o src/markovTable.o  src/parseArgs.o src/main.o
		g++ -std=c++14 $^ -o $@

all: tm
