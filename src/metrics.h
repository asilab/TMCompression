/**
    metrics.h
    Purpose: Mesure Behaviour of Turing Machines.

    @author Jorge Miguel Ferreira da Silva
    @version 0.1
*/

#pragma once
#include <vector>
#include "turingMachine.h"

struct Metrics{
  unsigned int amplitude;
  double selfCompression;
  double normalizedCompression;
};

struct CompressionResultsData
{
  // Integer
  std::vector <TmId> tmNumber;
  std::vector <unsigned int> amplitude;
  std::vector <double> normalized_compression;
  std::vector <double> self_compression;

  void append(TmId tmNumber,
  unsigned int amplitudes,
  double self_compression,
  double normalized_compression);
  
  void clear_data();
  void avg();

};
