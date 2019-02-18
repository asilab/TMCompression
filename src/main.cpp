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
struct CompressionResultsData
{
  std::vector <unsigned int> amplitudeResults;
  std::vector <double> normalizedCompressionResults;
  std::vector <double> selfCompressionResults;
};


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

/*
  * It will iterate through all the lines in file and
  * put them in given vector
*/

int main (int argc, char **argv){

  Args argument = parseArgs(argc,argv);

  auto data = tm(
    argument.states,
    argument.alphabet_size,
    argument.numIt,
    argument.k,
    argument.verbose);
  
  std::cout<< "TM \t k value \t iterations \t amplitude \t Self-Compression \t Normalized Compression " << std::endl; 
  std::cout<< "-------------------------------------------------" <<std::endl;

  for (auto i = 0u; i < data.amplitudeResults.size(); ++i) {
    std::cout << (i + 1) << "\t" << argument.k << "\t" << argument.numIt << "\t" << data.amplitudeResults[i] << "\t" 
    << std::setprecision(5) <<  data.selfCompressionResults[i] << "\t" << std::setprecision(5) << data.normalizedCompressionResults[i] << "\t" << std::endl;
  }

  std::cout<< "-------------------------------------------------" <<std::endl;
  float mean_amp = std::accumulate( data.amplitudeResults.begin(), data.amplitudeResults.end(), 0.0)/data.amplitudeResults.size();
  float mean_sc = std::accumulate( data.selfCompressionResults.begin(),  data.selfCompressionResults.end(), 0.0)/ data.selfCompressionResults.size();
  float mean_nc = std::accumulate( data.normalizedCompressionResults.begin(), data.normalizedCompressionResults.end(), 0.0)/data.normalizedCompressionResults.size();
  
  double sq_amp_sum = std::inner_product(data.amplitudeResults.begin(), data.amplitudeResults.end(), data.amplitudeResults.begin(), 0.0);
  double sq_sc_sum = std::inner_product(data.selfCompressionResults.begin(), data.selfCompressionResults.end(), data.selfCompressionResults.begin(), 0.0);
  double sq_nc_sum = std::inner_product(data.normalizedCompressionResults.begin(), data.normalizedCompressionResults.end(), data.normalizedCompressionResults.begin(), 0.0);

  double stdev_amp = std::sqrt(sq_amp_sum / data.amplitudeResults.size() - mean_amp * mean_amp);
  double stdev_sc = std::sqrt(sq_sc_sum / data.selfCompressionResults.size() - mean_sc * mean_sc);
  double stdev_nc = std::sqrt(sq_nc_sum / data.normalizedCompressionResults.size() - mean_nc * mean_nc);



  std::cout<< "Number of TM \t Mean Amp+/-std \t Mean sc+/-std \t Mean nc+/-std" << std::endl;
  std::cout << data.amplitudeResults.size() << "\t\t" << mean_amp << "+/-" << stdev_amp 
                                            << "\t\t" << mean_sc << "+/-" << stdev_sc 
                                            << "\t" << mean_nc << "+/-" << stdev_nc
                                            << std::endl;
}
 