/**
    parseArgs.h
    Purpose: Parse input arguments

    @author Jorge Miguel Ferreira da Silva
    @version 0.1
*/

#pragma once
#include <iostream>
#include "turingMachine.h"
#include <utility>
struct Args{
    size_t states = 0;
    size_t alphabet_size = 0;
    double threshold = 0.;
    unsigned int numIt = 0;
    std::vector <unsigned int> k; 
    std::pair < unsigned long long,bool> tm = std::make_pair(0ull, false);

    TraversalStrategy strategy = TraversalStrategy::SEQUENTIAL;
    unsigned long long n = 0;
    unsigned int jobs = 1;
    bool verbose = false;
};

Args parseArgs (int argc, char **argv);
void printArgs(Args);