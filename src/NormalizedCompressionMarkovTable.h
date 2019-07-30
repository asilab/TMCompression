
/**
    NormalizedCompressionMarkovTable.h
    Purpose: Measure Statistical Complexity of Turing Machine Tapes.

    @author Jorge Miguel Ferreira da Silva
    @version 0.1
*/

#pragma once

#include "metrics.h"
#include "markovTable.h"

struct NormalizedCompressionMarkovTable{
    
    MarkovTable mrkvTable;
    
    NormalizedCompressionMarkovTable(unsigned int k, unsigned int alphabet_size);

    Metrics update(const Tape& tape);
    Metrics update_string(const std::vector<unsigned int>& string_vector);
    CompressionResultsData profile_update_nc_mk_table(const Tape& tape, unsigned int divison);
    CompressionResultsData profile_update_nc_mk_table_random_string(const std::vector<unsigned int>& random_str, unsigned int division);
    double normalization_base(unsigned int length_of_tape, unsigned int cardinality);
    double normalization_profile(unsigned int cardinality);
    int sum_all_elements_vector(std::vector<unsigned int>& subvector_markovtable);
    double calculateLog(int index_value, int sum_all_line_elem);
    void reset();
};


 template <typename T> 
 struct BestKMarkovTables{ 
    std::vector<T> mrkvTables;

    BestKMarkovTables(const std::vector<unsigned int>& k, unsigned int alphabet_size){
        for (auto iterator = k.begin(); iterator != k.end(); ++iterator){
            mrkvTables.emplace_back(*iterator, alphabet_size);
        }
    }

    Metrics update(const Tape& tape){
        std::vector<unsigned int> amplitude;
        std::vector<double> sc;
        std::vector<double> nc;
        std::vector<double> k;
        Metrics bestMetrics;

        for (auto& mkvTable: this->mrkvTables) {
            Metrics results = mkvTable.update(tape);
            sc.push_back(results.selfCompression);
            amplitude.push_back(results.amplitude);
            nc.push_back(results.normalizedCompression);
            k.push_back(mkvTable.mrkvTable.k);
        }
        
        int min_index = std::distance(nc.begin(),std::min_element(std::begin(nc), std::end(nc)));
        bestMetrics.k=k[min_index];
        bestMetrics.amplitude = amplitude[min_index];
        bestMetrics.selfCompression = sc[min_index];
        bestMetrics.normalizedCompression = nc[min_index];

        return bestMetrics;
    };

    Metrics update_string(const std::vector<unsigned int>& string_vector){
        std::vector<unsigned int> amplitude;
        std::vector<double> sc;
        std::vector<double> nc;
        std::vector<double> k;
        Metrics bestMetrics;

        for (auto& mkvTable: this->mrkvTables) {
            Metrics results = mkvTable.update_string(string_vector);
            sc.push_back(results.selfCompression);
            amplitude.push_back(results.amplitude);
            nc.push_back(results.normalizedCompression);
            k.push_back(mkvTable.mrkvTable.k);
        }
        
        int min_index = std::distance(nc.begin(),std::min_element(std::begin(nc), std::end(nc)));
        bestMetrics.k=k[min_index];
        bestMetrics.amplitude = amplitude[min_index];
        bestMetrics.selfCompression = sc[min_index];
        bestMetrics.normalizedCompression = nc[min_index];
        return bestMetrics;
    }

    void reset() {
        for (auto& nmkt: this->mrkvTables){
            nmkt.mrkvTable.reset();
        }
    };

    CompressionResultsData profile_update_nc_mk_table(const Tape& tape, unsigned int division, const T& markovTable){
        return  markovTable.profile_update_nc_mk_table(tape, division);
    };

    CompressionResultsData  profile_update_nc_mk_table_random_string(const std::string& random_string, unsigned int division, const T& markovTable){
        std::vector<CompressionResultsData> allData;
        std::vector<double> sum_nc;

        for (auto& mkvTable: this->mrkvTables) {
            auto data = mkvTable.profile_update_nc_mk_table_random_string(random_string, division);
            allData.push_back(data);
            sum_nc.push_back(accumulate(data.normalized_compression.begin(),data.normalized_compression.end(),0));
        }
        int min_index = std::distance(sum_nc.begin(),std::min_element(std::begin(sum_nc), std::end(sum_nc)));
        return allData[min_index];
    };
};
