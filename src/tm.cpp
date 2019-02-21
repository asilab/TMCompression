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

  if (traversal_len == 0) {
    traversal_len = tm_cardinality(states, alphabet_size);
  }

  unsigned int counter = 0;
  do {
    auto metrics = run_machine(machine, normalizedCompressionMarkovTable, num_iterations);

    if (verbose && counter % 4096 == 0) {
      std::cerr << "TM #" << std::setw(8) << counter << ": amplitude = " << metrics.amplitude 
      << ": sc = " << std::setprecision(5) <<metrics.selfCompression <<": nc = " << std::setprecision(5) 
      << metrics.normalizedCompression << "\r";
    }

    machine.stMatrix.next();

    data.amplitude.push_back(metrics.amplitude);
    data.self_compression.push_back(metrics.selfCompression);
    data.normalized_compression.push_back(metrics.normalizedCompression);
    counter += 1;
  } while (counter < traversal_len);
  
  if (verbose) {
    std::cerr << std::endl;
  }
  return data;
}

        


void tmprofile(
    size_t states,
    size_t alphabet_size,
    unsigned int num_iterations,
    unsigned int k,
    unsigned long int tm_number)
    {

  TuringMachine machine(states, alphabet_size);
  CompressionResultsData data;
  NormalizedCompressionMarkovTable normalizedCompressionMarkovTable(k , alphabet_size);

  unsigned int counter = 0;
  do {    
    counter += 1;
    if (counter==tm_number){
      machine.reset_tape_and_state();
      for (auto i = 0u; i < num_iterations -1 ; ++i){
        normalizedCompressionMarkovTable.mrkvTable.reset();
        machine.act(); //importante ser antes
      }
      data = normalizedCompressionMarkovTable.profile_update_nc_mk_table(machine.turingTape);
      std::cout<< "TM \t k value \t iterations \t amplitude \t Self-Compression \t Normalized Compression " << std::endl; 
      std::cout<< "-------------------------------------------------" <<std::endl;
      for (auto i = 0u; i < data.amplitude.size(); ++i) {
      std::cout << (i + 1) << "\t" << data.amplitude[i] << "\t" << std::setprecision(5) <<  data.self_compression[i] 
                           << "\t" << std::setprecision(5) << data.normalized_compression[i] << "\t" << std::endl;
      }
      exit(0);

    }
  } while (machine.stMatrix.next());

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
        auto metrics = run_machine(machine, normalizedCompressionMarkovTable, *nb_it_val);

        data.amplitude.push_back(metrics.amplitude);
        data.self_compression.push_back(metrics.selfCompression);
        data.normalized_compression.push_back(metrics.normalizedCompression);

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
  std::cout<<  traversal_len<< threads<< std::endl;

  if (threads > traversal_len) {
    threads = traversal_len;
    if (verbose) {
      std::cerr << "Cardinality is low, using " << traversal_len << " threads instead" << std::endl;
    }
  }
  
  std::cout<<  traversal_len<< threads<< std::endl;
  // bugg
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
    total.amplitude.insert(end(total.amplitude), begin(r.amplitude), end(r.amplitude));
    total.normalized_compression.insert(end(total.normalized_compression), begin(r.normalized_compression), end(r.normalized_compression));
    total.self_compression.insert(end(total.self_compression), begin(r.self_compression), end(r.self_compression));
  }

  return total;
}


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

  if (strategy != TraversalStrategy::SEQUENTIAL) {
    throw std::invalid_argument("Sorry, only sequential traversal is currently implemented");
  }

  auto real_len = traversal_len > 0 ? traversal_len : tm_cardinality(states, alphabet_size);

  return multicore_sequential_partition([=](auto len, auto offset) {
      
      return tm(states, alphabet_size, num_iterations, k, strategy, len, offset, verbose);
    }, traversal_offset, real_len, threads, verbose);

}



void ktm_multicore(
    size_t states,
    size_t alphabet_size,
    unsigned int threads) {
  

  TuringMachine machine(states, alphabet_size);

  std::vector <unsigned int> range_of_k = {2,3,4,5,6,7,8,9,10};
  std::vector <unsigned int> range_of_it = {100, 1000, 10000};

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

