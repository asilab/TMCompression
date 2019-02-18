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
 