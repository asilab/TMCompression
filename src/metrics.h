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
  TuringRecord tr;
  unsigned int k;
  unsigned int amplitude;
  double selfCompression;
  double normalizedCompression;
  void print();
};
Metrics avg_metrics(std::vector<Metrics> vector_metrics);
std::vector<Metrics> ranking(std::vector<Metrics> vector_metrics, unsigned int amplitude_criteria);
Metrics get_first(const std::vector<Metrics>& vector_metrics);
struct IndexAndMetrics{
  TmId tmNumber;
  Metrics metrics;
};


struct AvgMetrics{
  std::pair<double,double> amp;
  std::pair<double,double> sc;
  std::pair<double,double> nc;
};


struct CompressionResultsData
{
  // Integer
  std::vector <unsigned int> kvalue;
  std::vector <TmId> tmNumber;
  std::vector <unsigned int> amplitude;
  std::vector <double> normalized_compression;
  std::vector <double> self_compression;

  void append(unsigned int k,
  TmId tmNumber,
  unsigned int amplitudes,
  double self_compression,
  double normalized_compression);
  
  void append_metrics(IndexAndMetrics);

  void clear_data();
  void merge(CompressionResultsData&& other);
  AvgMetrics avg();
  void print_profile_data(unsigned int divison);
  void print_data(unsigned int numIt);
  void print_avg_metrics(AvgMetrics avgMetrics);
};
