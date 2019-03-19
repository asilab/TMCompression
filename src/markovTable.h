/**
    markovTable.h
    Purpose: Make and fill Markov Tables.
             Mesure Statistical Complexity.

    @author Jorge Miguel Ferreira da Silva
    @version 0.1
*/

#pragma once
#include <vector>
#include <iostream>

#include "turingMachine.h"
#include "metrics.h"

using Char = unsigned int;

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



