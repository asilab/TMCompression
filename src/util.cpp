#include <vector>
#include <iostream>

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
/// Create the list of the number of machines with the growth of the number of states.
  void tm_growth_with_cardinality(size_t max_number_states){
    size_t min_number_states = 1;
    size_t alphabet_size=2;

    if (max_number_states< min_number_states){std::cerr<< "please insert number of states >= 1"<< std::endl; exit(0);}
     std::cout << "state" << "\t" <<"Number of Turing Machines"<< std::endl;

    for(auto state = min_number_states; state != max_number_states; ++state){
        std::cout << state << "\t" << tm_cardinality(state, alphabet_size) << std::endl;
    }
  }
  