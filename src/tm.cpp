#include <iostream>
#include <iomanip>
#include <vector>
#include <numeric>
#include <stdexcept>
#include <numeric>
#include <cmath>

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


void ktm(size_t states,
    size_t alphabet_size){

  TuringMachine machine(states, alphabet_size);

  std::vector <unsigned int> range_of_k = {2,3,4,5,6,7,8,9,10};
  std::vector <unsigned int> range_of_it = {100, 1000, 10000};
  CompressionResultsData data;
  unsigned int counter;
  for(auto kval = range_of_k.begin(); kval != range_of_k.end(); ++kval) {
    
    NormalizedCompressionMarkovTable normalizedCompressionMarkovTable(*kval, alphabet_size);
    
    for(auto nb_it_val = range_of_it.begin(); nb_it_val != range_of_it.end(); ++nb_it_val) {
      counter = 0;
      data.amplitude.clear();
      data.self_compression.clear();
      data.normalized_compression.clear();

      do {
        machine.reset_tape_and_state();
        for (auto i = 0u; i < *nb_it_val -1 ; ++i){
          normalizedCompressionMarkovTable.mrkvTable.reset();
          machine.act(); //importante ser antes
        }

        Metrics normalizedCompressionValue = normalizedCompressionMarkovTable.update_nc_mk_table(machine.turingTape);
        data.amplitude.push_back(normalizedCompressionValue.amplitude);
        data.self_compression.push_back(normalizedCompressionValue.selfCompression);
        data.normalized_compression.push_back(normalizedCompressionValue.normalizedCompression);

        normalizedCompressionMarkovTable.mrkvTable.reset();
        ++counter;
      } while (machine.stMatrix.next());

      float mean_amp = std::accumulate( data.amplitude.begin(), data.amplitude.end(), 0.0)/data.amplitude.size();
      float mean_sc = std::accumulate( data.self_compression.begin(),  data.self_compression.end(), 0.0)/ data.self_compression.size();
      float mean_nc = std::accumulate( data.normalized_compression.begin(), data.normalized_compression.end(), 0.0)/data.normalized_compression.size();
      
      double sq_amp_sum = std::inner_product(data.amplitude.begin(), data.amplitude.end(), data.amplitude.begin(), 0.0);
      double sq_sc_sum = std::inner_product(data.self_compression.begin(), data.self_compression.end(), data.self_compression.begin(), 0.0);
      double sq_nc_sum = std::inner_product(data.normalized_compression.begin(), data.normalized_compression.end(), data.normalized_compression.begin(), 0.0);

      double stdev_amp = std::sqrt(sq_amp_sum / data.amplitude.size() - mean_amp * mean_amp);
      double stdev_sc = std::sqrt(sq_sc_sum / data.self_compression.size() - mean_sc * mean_sc);
      double stdev_nc = std::sqrt(sq_nc_sum / data.normalized_compression.size() - mean_nc * mean_nc);

      std::cout<< "Number of TM \t k \t number iterations \tMean Amp+/-std \t Mean sc+/-std \t Mean nc+/-std" << std::endl;
      std::cout << data.amplitude.size() << "\t\t" << *kval 
                                         << "\t\t" << *nb_it_val 
                                         << "\t\t" << mean_amp << "+/-" << stdev_amp 
                                         << "\t\t" << mean_sc << "+/-" << stdev_sc 
                                         << "\t" << mean_nc << "+/-" << stdev_nc
                                         << std::endl;
    } 
  }
}
