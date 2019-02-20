#pragma once
#include <iostream>
#include "turingMachine.h"

struct Args{
    size_t states = 0;
    size_t alphabet_size = 0;
    double threshold = 0.;
    unsigned int numIt = 0;
    unsigned int k = 0;
    unsigned long int tm = 0;
    TraversalStrategy strategy = TraversalStrategy::SEQUENTIAL;
    bool verbose = false;
};

Args parseArgs (int argc, char **argv);
