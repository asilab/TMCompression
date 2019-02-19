#include <iostream>
#include <iomanip>
#include <vector>
#include <numeric>

#include "markovTable.h"
#include "turingMachine.h"
#include "tm.h"

/** Evaluate all relative turing machine programs with the given architecture.
 *
 * @param states
 * @param alphabet_size
 * @param num_iterations
 * @param k
 * @param verbose
 * @return a vector of normalized compression values, one per turing machine
 */

CompressionResultsData tm(
    size_t states,
    size_t alphabet_size,
    unsigned int num_iterations,
    unsigned int k,
    bool verbose) {

  TuringMachine machine(states, alphabet_size);
  CompressionResultsData data;
  NormalizedCompressionMarkovTable normalizedCompressionMarkovTable(k , alphabet_size);

  unsigned int counter = 0;  
  do { 
    machine.reset_tape_and_state();
    for (auto i = 0u; i < num_iterations -1 ; ++i){
      normalizedCompressionMarkovTable.mrkvTable.reset();
      machine.act(); //importante ser antes
    }
    Metrics normalizedCompressionValue = normalizedCompressionMarkovTable.update_nc_mk_table(machine.turingTape);
    data.amplitudeResults.push_back(normalizedCompressionValue.amplitude);
    data.selfCompressionResults.push_back(normalizedCompressionValue.selfCompression);
    data.normalizedCompressionResults.push_back(normalizedCompressionValue.normalizedCompression);

    if (verbose && counter % 65536 == 0) {
      std::cerr << "TM #" << std::setw(8) << counter << ": amplitude = " << normalizedCompressionValue.amplitude 
      << ": sc = " << std::setprecision(5) <<normalizedCompressionValue.selfCompression <<": nc = " << std::setprecision(5) 
      << normalizedCompressionValue.normalizedCompression << "\r";
    }
    counter += 1;
    normalizedCompressionMarkovTable.mrkvTable.reset();
  } while (machine.stMatrix.next());
  
  if (verbose) {
    std::cerr << std::endl;
  }
  return data;
}
