/**
    main.cpp
    Purpose: Run Program

    @author Jorge Miguel Ferreira da Silva
    @version 0.1
*/

#include <iostream>
#include <sstream>
#include <numeric>
#include <cmath>

#include "markovTable.h"
#include "turingMachine.h"
#include "parseArgs.h"

/*
  * It will iterate through all the lines in file and
  * put them in given vector
*/


int main (int argc, char **argv){

  Args argument = parseArgs(argc,argv);

  double NormalizedCompressionValue;
  TuringMachine machine(argument.states, argument.alphabet_size);
  float mean;
  double stdev;
  double sq_sum;
  std::vector <double> avg_nc_results;
  unsigned int counter = 0;
  bool normalizer = true;
  std::cout<< "TM \t k value \t iterations \t Compression Value " << std::endl; 
  std::cout<< "-------------------------------------------------" <<std::endl;    
  NormalizedCompressionMarkovTable normalizedCompressionMarkovTable(argument.k , argument.alphabet_size);
  counter = 0;

  do {
    //machine.stMatrix.print();    
    machine.reset();
    for (auto i = 0u; i < argument.numIt -1 ; ++i){
      normalizedCompressionMarkovTable.mrkvTable.reset();
      TapeMoves tpMove = machine.act(); //importante ser antes
    }
    NormalizedCompressionValue = normalizedCompressionMarkovTable.update_nc_mk_table(machine.turingTape,normalizer);
    avg_nc_results.push_back(NormalizedCompressionValue);
    std::cout << ++counter << "\t" << argument.k << "\t" << argument.numIt << "\t" <<  NormalizedCompressionValue << std::endl;
    normalizedCompressionMarkovTable.mrkvTable.reset();
  } while (machine.stMatrix.next());
  
  std::cout<< "-------------------------------------------------" <<std::endl;    
  mean = std::accumulate( avg_nc_results.begin(), avg_nc_results.end(), 0.0)/avg_nc_results.size(); 
  sq_sum = std::inner_product(avg_nc_results.begin(), avg_nc_results.end(), avg_nc_results.begin(), 0.0);
  stdev = std::sqrt(sq_sum / avg_nc_results.size() - mean * mean);
  std::cout<< "Number of TM \t Mean \t Standard deviation" << std::endl; 
  std::cout << avg_nc_results.size() << "\t" << mean << "\t" << stdev << std::endl;
}

