#include "util.h"

unsigned long long ipow(unsigned long long base, unsigned long long exp) {
    if (exp == 0) {
      return 1;
    }
    if (exp == 1) {
      return base;
    }
    int result = 1;
    for (;;)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        if (!exp)
            break;
        base *= base;
    }
    return result;
}

/// Calculate the full cardinality of all possible turing machine state matrices
  unsigned long long tm_cardinality(size_t states, size_t alphabet_size) {
    
    unsigned long long nstates = states;
    unsigned long long nalphabet = alphabet_size;
    auto record_cardinality = nstates * nalphabet * 3;

    return ipow(record_cardinality, nstates * nalphabet);
}
