/**
    main.cpp
    Purpose: Run Program

    @author Jorge Miguel Ferreira da Silva
    @version 0.1
*/


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
  
  
  data.print_data(argument.numIt);
  AvgMetrics avgMetrics = data.avg();
  data.print_avg_metrics(avgMetrics);

}