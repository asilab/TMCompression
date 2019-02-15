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

struct NormalizedCompressionMarkovTable{
    MarkovTable mrkvTable;
    NormalizedCompressionMarkovTable(unsigned int k, unsigned int alphabet_size);

    double update_nc_mk_table(const Tape& tape, bool normalize);
    double normalization_base(unsigned int length_of_tape, unsigned int cardinality);
    int sum_all_elements_vector(std::vector<unsigned int>& subvector_markovtable);
    double calculateLog(int index_value, int sum_all_line_elem);
};