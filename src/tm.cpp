/**
    tm.cpp
    Purpose: Various functions related to:
    - Profile of TM
    - Dynamical Profile of TM
    - Test various k
    - Mutithread TM
    - Cardinality of TM

    @author Jorge Miguel Ferreira da Silva
    @version 0.1
*/

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


/// The RNG engine for sampling random numbers in Monte Carlo.
using Rng = std::minstd_rand;

/** Calculate the full cardinality of all possible Turing machine state matrices.
 * @param states the state cardinality
 * @param alphabet_size the alphabet's size
 */
TmId tm_cardinality(unsigned int states, unsigned int alphabet_size) {
    TmId nstates = states;
    TmId nalphabet = alphabet_size;
    auto record_cardinality = nstates * nalphabet * 3;

    return ipow(record_cardinality, nstates * nalphabet);
}

/** Run the given Turing machine for a certain number of iterations.
 * Currently a private function.
 */
template <typename M>
IndexAndMetrics run_machine(TuringMachine& machine, M& compressionTable, unsigned int num_iterations) {
    IndexAndMetrics indMetrics;

    machine.reset_tape_and_state();
    for (auto i = 0u; i < num_iterations -1 ; ++i){
      compressionTable.reset();
      machine.act(); // grave esti antaŭe
    }

    indMetrics.metrics = compressionTable.update(machine.turingTape);
    compressionTable.reset();
    indMetrics.tmNumber = machine.stMatrix.calculate_index();
  return indMetrics;
}


/** Evaluate all relative Turing machine programs with the given architecture.
 *
 * @param states
 * @param alphabet_size
 * @param num_iterations
 * @param kvector vector of values of k
 * @param strategy the Turing machine traversal strategy
 * @param traversal_len number of different Turing machines to run, can be 0 in
 *        sequential traversal for the full TM domain
 * @param traversal_offset offset of the partition to travers (only in sequential strategy)
 * @param verbose
 * @return a struct containing the results of evaluation, one per Turing machine
 */
CompressionResultsData tm(
    size_t states,
    size_t alphabet_size,
    unsigned int num_iterations,
    const std::vector <unsigned int>& kvector,
    TraversalStrategy strategy,
    unsigned long long traversal_len,
    unsigned long long traversal_offset,
    bool verbose) {
      

  TuringMachine machine(states, alphabet_size);
  CompressionResultsData data;
  data.clear_data();

  BestKMarkovTables<NormalizedCompressionMarkovTable> bestMkvTableCompression(kvector, alphabet_size);
  
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
        
        auto indAndmetrics = run_machine(machine, bestMkvTableCompression, num_iterations);
        if (verbose && counter % 4096 == 0) {
          std::cerr << "TM #" << std::setw(8) << indAndmetrics.tmNumber << ": amplitude = " << indAndmetrics.metrics.amplitude 
          << ": sc = " << std::setprecision(5) << std::showpoint <<indAndmetrics.metrics.selfCompression <<": nc = " << std::setprecision(5) << std::showpoint 
          << indAndmetrics.metrics.normalizedCompression << "\r";
        }
        data.append_metrics(indAndmetrics);
        machine.stMatrix.next();
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
        auto indAndmetrics = run_machine(machine, bestMkvTableCompression, num_iterations);

        if (verbose && counter % 4096 == 0) {
          std::cerr << "TM #" << std::setw(8) << indAndmetrics.tmNumber << ": amplitude = " << indAndmetrics.metrics.amplitude 
          << ": sc = " << std::setprecision(5) << std::showpoint <<indAndmetrics.metrics.selfCompression <<": nc = " << std::setprecision(5) << std::showpoint
          << indAndmetrics.metrics.normalizedCompression << "\r";
        }
        
        // get Turing machine index
        data.append_metrics(indAndmetrics);
      }
    }
    break;
  }
  
  if (verbose) {
    std::cerr << std::endl;
  }
  return data;
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
    
    total.merge(std::move(r));    
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
    total.merge(std::move(r));    
  }

  return total;
}


CompressionResultsData tm_multicore(
    size_t states,
    size_t alphabet_size,
    unsigned int num_iterations,
    const std::vector<unsigned int> &kvector,
    TraversalStrategy strategy,
    unsigned long long traversal_len,
    unsigned long long traversal_offset,
    bool verbose,
    unsigned int threads){
    if (threads < 2) {
      return tm(states, alphabet_size, num_iterations, kvector, strategy, traversal_len, traversal_offset, verbose);
    }

    if (strategy == TraversalStrategy::SEQUENTIAL) {
      auto real_len = traversal_len > 0 ? traversal_len : tm_cardinality(states, alphabet_size);

      return multicore_sequential_partition([=](auto len, auto offset) {
        return tm(states, alphabet_size, num_iterations, kvector, strategy, len, offset, verbose);
          },real_len, traversal_offset,threads, verbose);
    } 
    else if (strategy == TraversalStrategy::MONTE_CARLO) {
    
      return multicore_monte_carlo([=](auto n) -> CompressionResultsData {
        return tm(states, alphabet_size, num_iterations, kvector, strategy, n, 0, verbose);
      }, traversal_len, threads, verbose);
    }

  throw std::runtime_error("unsupported traversal strategy");
}

/** Evaluates a specific Turing machine program dynamically,analysing the time complexity.
 * @param states
 * @param alphabet_size
 * @param num_iterations
 * @param k
 * @param tm_number
 */

void tm_dynamical_profile(
  size_t states,
  size_t alphabet_size,
  unsigned int num_iterations,
  unsigned int k,
  TmId tm_number,
  unsigned int divison)
  {
  IndexAndMetrics indxMetrics;
  indxMetrics.tmNumber=tm_number;
  TuringMachine machine(states, alphabet_size);
  CompressionResultsData data;
  NormalizedCompressionMarkovTable normalizedCompressionMarkovTable(k, alphabet_size);
  
  machine.stMatrix.set_by_index(tm_number);    
  machine.reset_tape_and_state();
  
  for (auto i = 0u; i < num_iterations -1 ; ++i){
    normalizedCompressionMarkovTable.mrkvTable.reset();
    machine.act(); //importante ser antes
    if(i%divison==0){
      indxMetrics.metrics = normalizedCompressionMarkovTable.update(machine.turingTape);
      data.append_metrics(indxMetrics);
    }
  }
  data.print_profile_data(divison);
}  

/** Evaluates a specific Turing machine Profile.
 *
 * @param states
 * @param alphabet_size
 * @param num_iterations
 * @param k
 * @param tm_number
 */
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
  data.print_profile_data(divison);
}

/** Replicate experiment to determine the best k and it for a given number of states and alphabet size.
 *
 * @param states
 * @param alphabet_size
 */
void ktm(size_t states,
    size_t alphabet_size){

  TuringMachine machine(states, alphabet_size);

  std::vector <unsigned int> range_of_k = {2,3,4,5,6,7,8,9,10};
  std::vector <unsigned int> range_of_it = {100, 1000, 10000};
  CompressionResultsData data;
  for(auto kval = range_of_k.begin(); kval != range_of_k.end(); ++kval) {
    
    NormalizedCompressionMarkovTable normalizedCompressionMarkovTable(*kval, alphabet_size);
    
    for(auto nb_it_val = range_of_it.begin(); nb_it_val != range_of_it.end(); ++nb_it_val) {

      data.clear_data();
      
      do {
        auto indAndmetrics = run_machine(machine, normalizedCompressionMarkovTable, *nb_it_val);

        data.append_metrics(indAndmetrics);

      } while (machine.stMatrix.next());

      auto avg_metrics = data.avg();

      std::cout<< "Number of TM \t k \t number iterations \tMean Amp+/-std \t Mean sc+/-std \t Mean nc+/-std" << std::endl;
      std::cout << data.amplitude.size() << "\t\t" << *kval 
                                         << "\t\t" << *nb_it_val 
                                         << "\t\t" << avg_metrics.amp.first << "+/-" << avg_metrics.amp.second 
                                         << "\t\t" << avg_metrics.sc.first << "+/-" << avg_metrics.sc.second 
                                         << "\t" << avg_metrics.nc.first << "+/-" << avg_metrics.nc.second
                                         << std::endl;
    } 
  }
}

/** Replicate experiment to determine the best k and it for a given number of states and alphabet size with the given architecture,
 * using multiple threads.
 *
 * @param states
 * @param alphabet_size
 * @param threads the number of threads to run in parallel
 */
void ktm_multicore(
    size_t states,
    size_t alphabet_size,
    unsigned int threads) {
  
  TuringMachine machine(states, alphabet_size);
  std::vector<unsigned int> kvalues;
  std::vector <unsigned int> range_of_k = {2,3,4,5,6,7,8,9,10};
  std::vector <unsigned int> range_of_it = {100, 1000, 10000};
  std::cout<< "Number of TM \t k \t number iterations \tMean Amp+/-std \t Mean sc+/-std \t Mean nc+/-std" << std::endl;
  for(auto kval = range_of_k.begin(); kval != range_of_k.end(); ++kval) {

    for(auto nb_it_val = range_of_it.begin(); nb_it_val != range_of_it.end(); ++nb_it_val) {
      kvalues.push_back(*kval);
      auto data = tm_multicore(states, alphabet_size, *nb_it_val, kvalues , TraversalStrategy::SEQUENTIAL, 0, 0, false, threads);
      kvalues.clear();
      AvgMetrics avgData = data.avg();
      data.print_avg_metrics(avgData);
      std::cout << "\t" << data.amplitude.size() << "\t\t" << *kval 
                                         << "\t\t" << *nb_it_val 
                                         << "\t\t" << avgData.amp.first << "+/-" << avgData.amp.second 
                                         << "\t\t" << avgData.sc.first << "+/-" << avgData.sc.second 
                                         << "\t" << avgData.nc.first << "+/-" << avgData.nc.second
                                         << std::endl;
    } 
  }
}

/**Tape of a Turing machine after n iterations
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
