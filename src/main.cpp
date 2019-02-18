/**
    main.cpp
    Purpose: Run Program

    @author Jorge Miguel Ferreira da Silva
    @version 0.1
*/

#include <iostream>
#include <iomanip>
#include <sstream>
#include <numeric>
#include <cmath>

#include "markovTable.h"
#include "turingMachine.h"
#include "parseArgs.h"

/** Evaluate all relative turing machine programs with the given architecture.
 *
 * @param states
 * @param alphabet_size
 * @param num_iterations
 * @param k
 * @param verbose
 * @return a vector of normalized compression values, one per turing machine
 */
std::vector<double> tm(
    size_t states,
    size_t alphabet_size,
    unsigned int num_iterations,
    unsigned int k,
    bool verbose) {
  TuringMachine machine(states, alphabet_size);
  std::vector <double> avg_nc_results;
  bool normalizer = true;
  NormalizedCompressionMarkovTable normalizedCompressionMarkovTable(k , alphabet_size);

  unsigned int counter = 0;  
  do { 
    machine.reset_tape_and_state();
    for (auto i = 0u; i < num_iterations -1 ; ++i){
      normalizedCompressionMarkovTable.mrkvTable.reset();
      machine.act(); //importante ser antes
    }
    double normalizedCompressionValue = normalizedCompressionMarkovTable.update_nc_mk_table(machine.turingTape, normalizer);
    avg_nc_results.push_back(normalizedCompressionValue);

    if (verbose && counter % 65536 == 0) {
      std::cerr << "TM #" << std::setw(8) << counter << ": ncv = " << normalizedCompressionValue << "\r";
    }
    counter += 1;
    normalizedCompressionMarkovTable.mrkvTable.reset();
  } while (machine.stMatrix.next());
  if (verbose) {
    std::cerr << std::endl;
  }
  return avg_nc_results;
}

/*
  * It will iterate through all the lines in file and
  * put them in given vector
*/

int main (int argc, char **argv){

  Args argument = parseArgs(argc,argv);

  auto avg_nc_results = tm(
    argument.states,
    argument.alphabet_size,
    argument.numIt,
    argument.k,
    argument.verbose);

  std::cout<< "TM \t k value \t iterations \t Compression Value " << std::endl;
  std::cout<< "-------------------------------------------------" <<std::endl;

  for (auto i = 0u; i < avg_nc_results.size(); ++i) {
    std::cout << (i + 1) << "\t" << argument.k << "\t" << argument.numIt << "\t" << avg_nc_results[i] << std::endl;
  }

  std::cout<< "-------------------------------------------------" <<std::endl;
  float mean = std::accumulate( avg_nc_results.begin(), avg_nc_results.end(), 0.0)/avg_nc_results.size();
  double sq_sum = std::inner_product(avg_nc_results.begin(), avg_nc_results.end(), avg_nc_results.begin(), 0.0);
  double stdev = std::sqrt(sq_sum / avg_nc_results.size() - mean * mean);
  std::cout<< "Number of TM \t Mean \t Standard deviation" << std::endl;
  std::cout << avg_nc_results.size() << "\t" << mean << "\t" << stdev << std::endl;
}
