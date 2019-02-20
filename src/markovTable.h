#pragma once
#include <vector>
#include <iostream>
#include "turingMachine.h"

using Char = unsigned int;

size_t ipow(size_t base, size_t exp);

struct MarkovTable{
  std::vector<int> markovVector;
  unsigned int alphSz;
  unsigned int k;

  MarkovTable(unsigned int k, unsigned int alphabet_size);
  
  int& at(const Char* characters);
  std::vector <unsigned int> getLine(const Char* characters);
  void reset();
  void print() const;

  private:
    size_t str_to_index(const Char* x);
};

struct Metrics{
  unsigned int amplitude;
  double selfCompression;
  double normalizedCompression;
};

struct CompressionResultsData
{
  std::vector <unsigned int> amplitude;
  std::vector <double> normalized_compression;
  std::vector <double> self_compression;
};

struct NormalizedCompressionMarkovTable{
    MarkovTable mrkvTable;
    NormalizedCompressionMarkovTable(unsigned int k, unsigned int alphabet_size);

    Metrics update_nc_mk_table(const Tape& tape);
    CompressionResultsData profile_update_nc_mk_table(const Tape& tape);
    double normalization_base(unsigned int length_of_tape, unsigned int cardinality);
    int sum_all_elements_vector(std::vector<unsigned int>& subvector_markovtable);
    double calculateLog(int index_value, int sum_all_line_elem);
};