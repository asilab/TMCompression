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


struct NormalizedCompressionMarkovTable{
    
    MarkovTable mrkvTable;
    
    NormalizedCompressionMarkovTable(unsigned int k, unsigned int alphabet_size);

    Metrics update(const Tape& tape);
    CompressionResultsData profile_update_nc_mk_table(const Tape& tape, unsigned int divison);
    double normalization_base(unsigned int length_of_tape, unsigned int cardinality);
    int sum_all_elements_vector(std::vector<unsigned int>& subvector_markovtable);
    double calculateLog(int index_value, int sum_all_line_elem);
    void reset();
};


 template <typename T> 
 struct BestKMarkovTables{ 
    std::vector<T> mrkvTables;

    BestKMarkovTables(const std::vector<unsigned int>& k, unsigned int alphabet_size){
        for (auto iterator = k.begin(); iterator != k.end(); ++iterator)
            mrkvTables.emplace_back(*iterator, alphabet_size);
    }

    Metrics update(const Tape& tape){
        std::vector<unsigned int> amplitude;
        std::vector<double> sc;
        std::vector<double> nc;
        Metrics bestMetrics;

        for (auto& mkvTable: this->mrkvTables) {
            Metrics results = mkvTable.update(tape);
            sc.push_back(results.selfCompression);
            amplitude.push_back(results.amplitude);
            nc.push_back(results.normalizedCompression);
        }

        int min_index = std::distance(nc.begin(),std::min_element(std::begin(nc), std::end(nc)));
        bestMetrics.amplitude = amplitude[min_index];
        bestMetrics.selfCompression = sc[min_index];
        bestMetrics.normalizedCompression = nc[min_index];
        return bestMetrics;
    };

    void reset() {
        for (auto& nmkt: this->mrkvTables){
            nmkt.mrkvTable.reset();
        }
    };

    CompressionResultsData profile_update_nc_mk_table(const Tape& tape, unsigned int divison, const T& markovTable){
        return  markovTable.profile_update_nc_mk_table(tape);
    };
};

