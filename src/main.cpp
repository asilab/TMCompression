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
