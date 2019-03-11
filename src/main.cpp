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
      << std::setprecision(5) << std::showpoint <<  data.self_compression[i] << "\t" << std::setprecision(5) << std::showpoint << data.normalized_compression[i] << "\t" << std::endl;
    }
  }
  else if (argument.strategy == TraversalStrategy::MONTE_CARLO){
    //std::cout <<data.tmNumber.size()<<std::endl;

    for (auto i = 0u; i < data.amplitude.size(); ++i) {
    std::cout << data.tmNumber[i] << "\t" << argument.k << "\t" << argument.numIt << "\t" << data.amplitude[i] << "\t" 
    << std::setprecision(5)  << std::showpoint <<  data.self_compression[i] << "\t" << std::setprecision(5) 
    << std::showpoint << data.normalized_compression[i] << "\t" << std::endl;
    }
  }

  std::cout<< "-------------------------------------------------" <<std::endl;
  AvgMetrics avgMetrics = data.avg();

  data.print_avg_metrics(avgMetrics);

}