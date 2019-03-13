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


// // Create vector of MarkovTables?
 template <typename T> 
 struct BestKMarkovTables{ 
    std::vector<T> mrkvTables;

    BestKMarkovTables(const std::vector<unsigned int>& k, unsigned int alphabet_size){
        for (auto iterator = k.begin(); iterator != k.end(); ++iterator)
            mrkvTables.emplace_back(k, alphabet_size);
    }


    Metrics bestMetrics(const Tape& tape){
        std::vector<unsigned int> amplitude;
        std::vector<double> sc;
        std::vector<double> nc;
        Metrics bestMetrics;
        Metrics results;
        for (auto& mkvTable: this->mrkvTables) {
            results = update(tape, mkvTable);

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

    
    Metrics update(const Tape& tape,const T& mkvTable) {
        return mkvTable.update(tape);
    };
    
    double normalization_base(unsigned int length_of_tape, unsigned int cardinality){
        return ( length_of_tape * log2(cardinality) ); 
    };

    int sum_all_elements_vector(std::vector<unsigned int>& subvector_markovtable){
        int sum_of_elems = 0;

        for (auto& n : subvector_markovtable){
            sum_of_elems += n;
            }
        return sum_of_elems;
    };

    double calculateLog(int index_value, int sum_all_line_elem){
        double value = static_cast<double>(index_value)/ static_cast<double>(sum_all_line_elem);
        //std::cout << "value div = " << value << std::endl ;
        return (- log2(value));
    };

    void reset() {
        for (auto& nmkt: this->mrkvTables){
            *nmkt.mrkvTable.reset();
        }
    };

    CompressionResultsData profile_update_nc_mk_table(const Tape& tape, unsigned int divison, T markovTable){
        auto b = begin(tape.tape) + tape.ind_left- markovTable.k  + 1 ; // To have k context at the beginning    
        auto e = begin(tape.tape) + tape.ind_right - markovTable.k;
        CompressionResultsData data;

        unsigned int diff_indexes = (tape.ind_right) - (tape.ind_left + 1);
        unsigned int counter=0;

        for (auto it = b; it != e; ++it) {
            ++counter;
            auto indxvalue = markovTable.at(&*it) + 1;
            auto subvectorOfMarkovTable = markovTable.getLine(&*it); 
            std::transform(subvectorOfMarkovTable.begin(), subvectorOfMarkovTable.end(), subvectorOfMarkovTable.begin(), bind2nd(std::plus<int>(), 1)); 
            double logaritm = calculateLog(indxvalue    ,   sum_all_elements_vector(subvectorOfMarkovTable));
            markovTable.at(&*it)+=1;
            if(diff_indexes<=5){       
                data.amplitude.push_back(counter);
                data.self_compression.push_back(logaritm);
                data.normalized_compression.push_back(logaritm/normalization_base(diff_indexes, markovTable.alphSz));
            }
            else if (counter % divison ==0){
                data.amplitude.push_back(counter);
                data.self_compression.push_back(logaritm);
                data.normalized_compression.push_back(logaritm/normalization_base(diff_indexes, markovTable.alphSz));
            }
        }
        return  data; 
    };
};

