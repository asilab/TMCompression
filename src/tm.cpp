#include <iostream>
#include <iomanip>
#include <vector>
#include <numeric>
#include <stdexcept>

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
 * @return a struct containing the results of evaluation, one per turing machine
 */
CompressionResultsData tm(
    size_t states,
    size_t alphabet_size,
    unsigned int num_iterations,
    unsigned int k,
    TraversalStrategy strategy,
    unsigned long long traversal_len,
    unsigned long long traversal_offset,
    bool verbose) {

  TuringMachine machine(states, alphabet_size);
  CompressionResultsData data;
  NormalizedCompressionMarkovTable normalizedCompressionMarkovTable(k , alphabet_size);

  if (strategy != TraversalStrategy::SEQUENTIAL) {
    throw std::invalid_argument("Sorry, only sequential traversal is currently implemented");
  }

  if (traversal_offset > 0) {
    machine.stMatrix.set_by_index(traversal_offset);
  }

  unsigned int counter = 0;
  do {
    machine.reset_tape_and_state();
    for (auto i = 0u; i < num_iterations -1 ; ++i){
      normalizedCompressionMarkovTable.mrkvTable.reset();
      machine.act(); //importante ser antes
    }
    Metrics normalizedCompressionValue = normalizedCompressionMarkovTable.update_nc_mk_table(machine.turingTape);
    data.amplitude.push_back(normalizedCompressionValue.amplitude);
    data.self_compression.push_back(normalizedCompressionValue.selfCompression);
    data.normalized_compression.push_back(normalizedCompressionValue.normalizedCompression);

    if (verbose && counter % 4096 == 0) {
      std::cerr << "TM #" << std::setw(8) << counter << ": amplitude = " << normalizedCompressionValue.amplitude 
      << ": sc = " << std::setprecision(5) <<normalizedCompressionValue.selfCompression <<": nc = " << std::setprecision(5) 
      << normalizedCompressionValue.normalizedCompression << "\r";
    }
    counter += 1;
    normalizedCompressionMarkovTable.mrkvTable.reset();
  } while ((traversal_len == 0 && machine.stMatrix.next()) || counter < traversal_len);
  
  if (verbose) {
    std::cerr << std::endl;
  }
  return data;
}
