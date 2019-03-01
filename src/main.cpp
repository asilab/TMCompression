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

#include "tm.h"
#include "parseArgs.h"

 
/*
  * It will iterate through all the lines in file and
  * put them in given vector
*/

int main (int argc, char **argv){

  Args argument = parseArgs(argc,argv);

  auto data = tm_multicore(
    argument.states,
    argument.alphabet_size,
    argument.numIt,
    argument.k,
    argument.strategy,
    argument.n,
    0,
    argument.verbose,
    argument.jobs);
  
  std::cout<< "TM \t k value \t iterations \t amplitude \t Self-Compression \t Normalized Compression " << std::endl; 
  std::cout<< "-------------------------------------------------" <<std::endl;
  if (argument.strategy == TraversalStrategy::SEQUENTIAL){
    for (auto i = 0u; i < data.amplitude.size(); ++i) {
      std::cout << (i + 1) << "\t" << argument.k << "\t" << argument.numIt << "\t" << data.amplitude[i] << "\t" 
      << std::setprecision(5) <<  data.self_compression[i] << "\t" << std::setprecision(5) << data.normalized_compression[i] << "\t" << std::endl;
    }
  }
  else if (argument.strategy != TraversalStrategy::SEQUENTIAL){
    for (auto i = 0u; i < data.amplitude.size(); ++i) {
    std::cerr <<"under work" <<std::endl;
    // change (i+1) to data.tmNumber[i];
    std::cout << (i + 1) << "\t" << argument.k << "\t" << argument.numIt << "\t" << data.amplitude[i] << "\t" 
    << std::setprecision(5) <<  data.self_compression[i] << "\t" << std::setprecision(5) << data.normalized_compression[i] << "\t" << std::endl;
    }
  }

  std::cout<< "-------------------------------------------------" <<std::endl;
  float mean_amp = std::accumulate( data.amplitude.begin(), data.amplitude.end(), 0.0)/data.amplitude.size();
  float mean_sc = std::accumulate( data.self_compression.begin(),  data.self_compression.end(), 0.0)/ data.self_compression.size();
  float mean_nc = std::accumulate( data.normalized_compression.begin(), data.normalized_compression.end(), 0.0)/data.normalized_compression.size();
  
  double sq_amp_sum = std::inner_product(data.amplitude.begin(), data.amplitude.end(), data.amplitude.begin(), 0.0);
  double sq_sc_sum = std::inner_product(data.self_compression.begin(), data.self_compression.end(), data.self_compression.begin(), 0.0);
  double sq_nc_sum = std::inner_product(data.normalized_compression.begin(), data.normalized_compression.end(), data.normalized_compression.begin(), 0.0);

  double stdev_amp = std::sqrt(sq_amp_sum / data.amplitude.size() - mean_amp * mean_amp);
  double stdev_sc = std::sqrt(sq_sc_sum / data.self_compression.size() - mean_sc * mean_sc);
  double stdev_nc = std::sqrt(sq_nc_sum / data.normalized_compression.size() - mean_nc * mean_nc);



  std::cout<< "Number of TM \t Mean Amp+/-std \t Mean sc+/-std \t Mean nc+/-std" << std::endl;
  std::cout << data.amplitude.size() << "\t\t" << mean_amp << "+/-" << stdev_amp 
                                              << "\t\t" << mean_sc << "+/-" << stdev_sc 
                                              << "\t" << mean_nc << "+/-" << stdev_nc
                                              << std::endl;
}