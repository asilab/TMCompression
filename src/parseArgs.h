#pragma once
#include <iostream>

struct Args{
    size_t states;
    size_t alphabet_size;
    double threshold;
    unsigned int numIt;
    unsigned int k;
};

Args parseArgs (int argc, char **argv);
