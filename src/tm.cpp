#include <iostream>
#include <iomanip>
#include <vector>
#include <numeric>
#include <stdexcept>
#include <cmath>
#include <thread>
#include <future>
#include <type_traits>

#include "markovTable.h"
#include "turingMachine.h"
#include "util.h"
#include "tm.h"

/** Run the given turing machine for a certain number of iterations.
 * Currently a private function.
 */
Metrics run_machine(TuringMachine& machine, NormalizedCompressionMarkovTable& normalizedCompressionMarkovTable, unsigned int num_iterations) {
    machine.reset_tape_and_state();
    for (auto i = 0u; i < num_iterations -1 ; ++i){
      normalizedCompressionMarkovTable.mrkvTable.reset();
      machine.act(); // grave esti antaŭe
    }
    Metrics metrics = normalizedCompressionMarkovTable.update_nc_mk_table(machine.turingTape);
    normalizedCompressionMarkovTable.mrkvTable.reset();
  return metrics;
}

/// The RNG engine for sampling random numbers in Monte Carlo.
using Rng = std::minstd_rand;

/** Calculate the full cardinality of all possible turing machine state matrices.
 * @param states the state cardinality
 * @param alphabet_size the alphabet's size
 */
TmId tm_cardinality(unsigned int states, unsigned int alphabet_size) {
    TmId nstates = states;
    TmId nalphabet = alphabet_size;
    auto record_cardinality = nstates * nalphabet * 3;

    return ipow(record_cardinality, nstates * nalphabet);
}

/** Evaluate all relative turing machine programs with the given architecture.
 *
 * @param states
 * @param alphabet_size
 * @param num_iterations
 * @param k
 * @param strategy the turing machine traversal strategy
 * @param traversal_len number of different turing machines to run, can be 0 in
 *        sequential traversal for the full TM domain
 * @param traversal_offset offset of the partition to travers (only in sequential strategy)
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

  switch (strategy) {
    case TraversalStrategy::SEQUENTIAL: {
      if (traversal_offset > 0) {
        machine.stMatrix.set_by_index(traversal_offset);
      }
      if (traversal_len == 0) {
        traversal_len = tm_cardinality(states, alphabet_size);
      }

      unsigned int counter = 0;
      do {
        auto metrics = run_machine(machine, normalizedCompressionMarkovTable, num_iterations);

        if (verbose && counter % 4096 == 0) {
          std::cerr << "TM #" << std::setw(8) << counter << ": amplitude = " << metrics.amplitude 
          << ": sc = " << std::setprecision(5) << std::showpoint <<metrics.selfCompression <<": nc = " << std::setprecision(5) << std::showpoint 
          << metrics.normalizedCompression << "\r";
        }

        machine.stMatrix.next();
        data.amplitude.push_back(metrics.amplitude);
        data.self_compression.push_back(metrics.selfCompression);
        data.normalized_compression.push_back(metrics.normalizedCompression);
        counter += 1;
      } while (counter < traversal_len);
    }
    break;
    case TraversalStrategy::MONTE_CARLO: {
      // initialize random number generator
      std::random_device rnd_device;
      Rng rng{rnd_device()};

      for (auto counter = 0ull; counter < traversal_len; counter++) {
        machine.stMatrix.set_random(rng);
        auto index = machine.stMatrix.calculate_index();
        auto metrics = run_machine(machine, normalizedCompressionMarkovTable, num_iterations);

        if (verbose && counter % 4096 == 0) {
          std::cerr << "TM #" << std::setw(8) << counter << ": amplitude = " << metrics.amplitude 
          << ": sc = " << std::setprecision(5) << std::showpoint <<metrics.selfCompression <<": nc = " << std::setprecision(5) << std::showpoint
          << metrics.normalizedCompression << "\r";
        }
        
        // get turing machine index
        data.tmNumber.push_back(index);
        data.amplitude.push_back(metrics.amplitude);
        data.self_compression.push_back(metrics.selfCompression);
        data.normalized_compression.push_back(metrics.normalizedCompression);
      }
    }
    break;
  }
  
  if (verbose) {
    std::cerr << std::endl;
  }
  return data;
}

/**Tape of a Turing machine after n interations
 * 
 * @param states
 * @param alphabet_size
 * @param num_iterations
 * @param tm_number
 */
void tm_print_tape(
  size_t states,
  size_t alphabet_size,
  unsigned int num_iterations,
  TmId tm_number)
  {
  
  TuringMachine machine(states, alphabet_size);    
  machine.stMatrix.set_by_index(tm_number); 
  machine.reset_tape_and_state();
  for (auto i = 0u; i < num_iterations -1 ; ++i){
          machine.act(); //importante ser antes
  }
  machine.turingTape.print();
}

/**Print State matrix of a Turing machine
 * 
 * @param states
 * @param alphabet_size
 * @param tm_number
 */
void tm_print_state_matrix(
  size_t states,
  size_t alphabet_size,
  TmId tm_number){

  TuringMachine machine(states, alphabet_size);    
  machine.stMatrix.set_by_index(tm_number); 
  machine.stMatrix.print();
}


void tm_dynamical_profile(
  size_t states,
  size_t alphabet_size,
  unsigned int num_iterations,
  unsigned int k,
  TmId tm_number,
  unsigned int divison)
  {

  TuringMachine machine(states, alphabet_size);
  CompressionResultsData data;
  NormalizedCompressionMarkovTable normalizedCompressionMarkovTable(k, alphabet_size);
  
  machine.stMatrix.set_by_index(tm_number);    
  machine.reset_tape_and_state();

  for (auto i = 0u; i < num_iterations -1 ; ++i){
    normalizedCompressionMarkovTable.mrkvTable.reset();
    machine.act(); //importante ser antes
    if(i%divison==0){
      Metrics metrics = normalizedCompressionMarkovTable.update_nc_mk_table(machine.turingTape);
      data.amplitude.push_back(metrics.amplitude); 
      data.normalized_compression.push_back(metrics.normalizedCompression);
      data.self_compression.push_back(metrics.selfCompression);
    }
  }
  std::cout<< "iterations \t amplitude \t Self-Compression \t Normalized Compression " << std::endl; 
  std::cout<< "-------------------------------------------------" <<std::endl;
  for (auto i = 0u; i < data.amplitude.size(); ++i) {
  std::cout << ((i + 1) * divison) << "\t" << data.amplitude[i] << "\t" << std::setprecision(5) << std::showpoint <<  data.self_compression[i] 
                        << "\t" << std::setprecision(5) << std::showpoint << data.normalized_compression[i] << "\t" << std::endl;
  }
}  

void tm_profile(
  size_t states,
  size_t alphabet_size,
  unsigned int num_iterations,
  unsigned int k,
  TmId tm_number,
  unsigned int divison)
  {

  TuringMachine machine(states, alphabet_size);
  CompressionResultsData data;
  NormalizedCompressionMarkovTable normalizedCompressionMarkovTable(k , alphabet_size);
  
  machine.stMatrix.set_by_index(tm_number); 
  machine.reset_tape_and_state();
  for (auto i = 0u; i < num_iterations -1 ; ++i){
    normalizedCompressionMarkovTable.mrkvTable.reset();
    machine.act(); //importante ser antes
  }
  data = normalizedCompressionMarkovTable.profile_update_nc_mk_table(machine.turingTape, divison);

  std::cout<< "iterations \t amplitude \t Self-Compression \t Normalized Compression " << std::endl; 
  std::cout<< "-------------------------------------------------" <<std::endl;
  
  for (auto i = 0u; i < data.amplitude.size(); ++i) {
    std::cout << ((i + 1)*divison) << "\t" << data.amplitude[i] << "\t" << std::setprecision(5)  << std::showpoint <<  data.self_compression[i] 
                        << "\t" << std::setprecision(5) << std::showpoint << data.normalized_compression[i] << "\t" << std::endl;
  }
}


void ktm(size_t states,
    size_t alphabet_size){

  TuringMachine machine(states, alphabet_size);

  std::vector <unsigned int> range_of_k = {2,3,4,5,6,7,8,9,10};
  std::vector <unsigned int> range_of_it = {100, 1000, 10000};
  CompressionResultsData data;
  for(auto kval = range_of_k.begin(); kval != range_of_k.end(); ++kval) {
    
    NormalizedCompressionMarkovTable normalizedCompressionMarkovTable(*kval, alphabet_size);
    
    for(auto nb_it_val = range_of_it.begin(); nb_it_val != range_of_it.end(); ++nb_it_val) {

      data.amplitude.clear();
      data.self_compression.clear();
      data.normalized_compression.clear();

      do {
        auto metrics = run_machine(machine, normalizedCompressionMarkovTable, *nb_it_val);

        data.amplitude.push_back(metrics.amplitude);
        data.self_compression.push_back(metrics.selfCompression);
        data.normalized_compression.push_back(metrics.normalizedCompression);

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

/** Perform tasks in parallel by performing the same operation `n` times over
 * `threads` workers. Each worker will then make its own random number
 * generator.
 */
template <typename F>
CompressionResultsData multicore_monte_carlo(
      F f,
      size_t n,
      unsigned int threads,
      bool verbose) {

  // split work in partitions
  if (threads > n) {
    threads = n;
    if (verbose) {
      std::cerr << "Number of runs is low, using " << n << " threads instead" << std::endl;
    }
  }
  
  auto worker_n = n / threads;
  auto worker_rest = n % threads;

  // spawn  tasks asynchronously
  std::vector<std::future<CompressionResultsData>> jobs;
  for (auto i = 0u; i < threads; ++i) {
    auto len = worker_n;
    if (i == threads - 1) {
      len += worker_rest;
    }
    jobs.push_back(std::async([=]() {
      if (verbose) {
        std::cerr << "Worker #" << i << " started" << std::endl;
      }
      auto o = f(len);
      if (verbose) {
        std::cerr << "Worker #" << i << " finished" << std::endl;
      }

      return o;
    }));
  }

  // await and merge results together

  CompressionResultsData total;

  for (auto& f: jobs) {
    auto r = f.get();
    total.tmNumber.insert(end(total.tmNumber),begin(r.tmNumber),end(r.tmNumber));
    total.amplitude.insert(end(total.amplitude), begin(r.amplitude), end(r.amplitude));
    total.normalized_compression.insert(end(total.normalized_compression), begin(r.normalized_compression), end(r.normalized_compression));
    total.self_compression.insert(end(total.self_compression), begin(r.self_compression), end(r.self_compression));
  }

  return total;
}

/** Perform tasks in parallel by sequentially partitioning an
 * interval to `threads` workers.
 */
template <typename F>
CompressionResultsData multicore_sequential_partition(
      F f,
      unsigned long long traversal_len,
      unsigned long long traversal_offset,
      unsigned int threads,
      bool verbose) {
  // split work in partitions

  if (threads > traversal_len) {
    threads = traversal_len;
    if (verbose) {
      std::cerr << "Cardinality is low, using " << traversal_len << " threads instead" << std::endl;
    }
  }
  
  auto partition_len = traversal_len / threads;
  auto partition_rest = traversal_len % threads;

  // spawn  tasks asynchronously
  std::vector<std::future<CompressionResultsData>> jobs;
  for (auto i = 0u; i < threads; ++i) {
    auto offset = traversal_offset + partition_len * i;
    auto len = partition_len;
    if (i == threads - 1) {
      len += partition_rest;
    }

    jobs.push_back(std::async([=]() {
      if (verbose) {
        std::cerr << "Worker #" << i << " started @ partition [" << offset << ", " << (offset + len) <<  "[" << std::endl;
      }
      auto o = f(len, offset);
      if (verbose) {
        std::cerr << "Worker #" << i << " finished" << std::endl;
      }

      return o;
    }));
  }

  // await and merge results together

  CompressionResultsData total;

  for (auto& f: jobs) {
    auto r = f.get();
    total.tmNumber.insert(end(total.tmNumber),begin(r.tmNumber),end(r.tmNumber));
    total.amplitude.insert(end(total.amplitude), begin(r.amplitude), end(r.amplitude));
    total.normalized_compression.insert(end(total.normalized_compression), begin(r.normalized_compression), end(r.normalized_compression));
    total.self_compression.insert(end(total.self_compression), begin(r.self_compression), end(r.self_compression));
  }

  return total;
}


/*
tm_multicore(
    argument.states,
    argument.alphabet_size,
    argument.numIt,
    argument.k,
    argument.strategy,
    argument.n,
    0,
    argument.verbose,
    argument.jobs);
  
*/

CompressionResultsData tm_multicore(
    size_t states,
    size_t alphabet_size,
    unsigned int num_iterations,
    unsigned int k,
    TraversalStrategy strategy,
    unsigned long long traversal_len,
    unsigned long long traversal_offset,
    bool verbose,
    unsigned int threads)
{
  if (threads < 2) {
    return tm(states, alphabet_size, num_iterations, k, strategy, traversal_len, traversal_offset, verbose);
  }

  if (strategy == TraversalStrategy::SEQUENTIAL) {
    auto real_len = traversal_len > 0 ? traversal_len : tm_cardinality(states, alphabet_size);

    return multicore_sequential_partition([=](auto len, auto offset) {
      return tm(states, alphabet_size, num_iterations, k, strategy, len, offset, verbose);
        },real_len, traversal_offset,threads, verbose);
  } 
  else if (strategy == TraversalStrategy::MONTE_CARLO) {
  
    return multicore_monte_carlo([=](auto n) -> CompressionResultsData {
      return tm(states, alphabet_size, num_iterations, k, strategy, n, 0, verbose);
    }, traversal_len, threads, verbose);
  }

  throw std::runtime_error("unsupported traversal strategy");
}


void ktm_multicore(
    size_t states,
    size_t alphabet_size,
    unsigned int threads) {
  
  TuringMachine machine(states, alphabet_size);

  std::vector <unsigned int> range_of_k = {2,3,4,5,6,7,8,9,10};
  std::vector <unsigned int> range_of_it = {100, 1000, 10000};
  std::cout<< "Number of TM \t k \t number iterations \tMean Amp+/-std \t Mean sc+/-std \t Mean nc+/-std" << std::endl;
  for(auto kval = range_of_k.begin(); kval != range_of_k.end(); ++kval) {

    for(auto nb_it_val = range_of_it.begin(); nb_it_val != range_of_it.end(); ++nb_it_val) {
      auto data = tm_multicore(states, alphabet_size, *nb_it_val, *kval, TraversalStrategy::SEQUENTIAL, 0, 0, false, threads);
      float mean_amp = std::accumulate( data.amplitude.begin(), data.amplitude.end(), 0.0)/data.amplitude.size();
      float mean_sc = std::accumulate( data.self_compression.begin(),  data.self_compression.end(), 0.0)/ data.self_compression.size();
      float mean_nc = std::accumulate( data.normalized_compression.begin(), data.normalized_compression.end(), 0.0)/data.normalized_compression.size();
      double sq_amp_sum = std::inner_product(data.amplitude.begin(), data.amplitude.end(), data.amplitude.begin(), 0.0);
      double sq_sc_sum = std::inner_product(data.self_compression.begin(), data.self_compression.end(), data.self_compression.begin(), 0.0);
      double sq_nc_sum = std::inner_product(data.normalized_compression.begin(), data.normalized_compression.end(), data.normalized_compression.begin(), 0.0);
      double stdev_amp = std::sqrt(sq_amp_sum / data.amplitude.size() - mean_amp * mean_amp);
      double stdev_sc = std::sqrt(sq_sc_sum / data.self_compression.size() - mean_sc * mean_sc);
      double stdev_nc = std::sqrt(sq_nc_sum / data.normalized_compression.size() - mean_nc * mean_nc);

      std::cout << "\t" << data.amplitude.size() << "\t\t" << *kval 
                                         << "\t\t" << *nb_it_val 
                                         << "\t\t" << mean_amp << "+/-" << stdev_amp 
                                         << "\t\t" << mean_sc << "+/-" << stdev_sc 
                                         << "\t" << mean_nc << "+/-" << stdev_nc
                                         << std::endl;
    } 
  }
}

