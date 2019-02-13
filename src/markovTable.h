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

  MarkovTable(unsigned int k, unsigned int alphabeth_size);
  
  int& at(const Char* characters);
  std::vector <unsigned int> getLine(const Char* characters);
  void reset();
  void print() const;

  private:
    size_t str_to_index(const Char* x);
};

struct FillMarkovTable{
    MarkovTable mrkvTable;
    bool isfilled;
    FillMarkovTable(unsigned int k, unsigned int alphabeth_size);
    void fill(Tape tape);
    void it_update_table(TapeMoves tpMv, Tape tape); //new stuff
    void update_table(TapeMoves tpMv, Tape tape);
};

struct NormalizedCompressionMarkovTable{
    MarkovTable mrkvTable;
    bool isfilled;
    NormalizedCompressionMarkovTable(unsigned int k, unsigned int alphabeth_size);

    double update_nc_mk_table(Tape tape);
    double normalization_base(unsigned int length_of_tape, unsigned int cardinality);
    int sum_all_elements_vector(std::vector<unsigned int>& subvector_markovtable);
    double calculateLog(int index_value, int sum_all_line_elem);
};