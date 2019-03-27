/**
    NormalizedCompressionMarkovTable.cpp
    Purpose: Mesure Statistical Complexity of Turing Machine Tapes.

    @author Jorge Miguel Ferreira da Silva
    @version 0.1
*/

#include "metrics.h"
#include "NormalizedCompressionMarkovTable.h"
#include "util.h"

NormalizedCompressionMarkovTable::NormalizedCompressionMarkovTable(unsigned int k, unsigned int alphabet_size):
mrkvTable(k, alphabet_size) {}

Metrics NormalizedCompressionMarkovTable::update(const Tape& tape){

    auto b = tape.ind_left - this->mrkvTable.k  + 1 ; // To have k context at the begining    
    auto e = tape.ind_right - this->mrkvTable.k;

    Metrics metrics;
    metrics.k = this->mrkvTable.k;

    double value = 0;
    
    
    for (auto it = b; it != e; ++it) {
        //tape.print();
        auto indxvalue = this->mrkvTable.at(&tape.tape[it]) + 1;
        auto subvectorOfMarkovTable = this->mrkvTable.getLine(&tape.tape[it]); 
        std::transform(subvectorOfMarkovTable.begin(), subvectorOfMarkovTable.end(), subvectorOfMarkovTable.begin(), bind2nd(std::plus<int>(), 1)); 
        double logaritm = calculateLog(indxvalue, sum_all_elements_vector(subvectorOfMarkovTable));
        value += logaritm;
        this->mrkvTable.at(&tape.tape[it])+=1;
    }
    
    metrics.selfCompression = value;
    unsigned int diff_indexes = (tape.ind_right) - (tape.ind_left + 1);
    metrics.amplitude = diff_indexes;
    metrics.normalizedCompression = (value/normalization_base(diff_indexes, this->mrkvTable.alphSz));
    return  metrics; 
}

//obtain all values of specific table
CompressionResultsData NormalizedCompressionMarkovTable::profile_update_nc_mk_table(const Tape& tape, unsigned int division){
    auto b = begin(tape.tape) + tape.ind_left- this->mrkvTable.k  + 1 ; // To have k context at the beginning    
    auto e = begin(tape.tape) + tape.ind_right - this->mrkvTable.k;
    CompressionResultsData data;

    unsigned int diff_indexes= (tape.ind_right) - (tape.ind_left + 1);
    unsigned int counter=0;

    for (auto it = b; it != e; ++it) {
        ++counter;
        auto indxvalue = this->mrkvTable.at(&*it) + 1;
        auto subvectorOfMarkovTable = this->mrkvTable.getLine(&*it); 
        std::transform(subvectorOfMarkovTable.begin(), subvectorOfMarkovTable.end(), subvectorOfMarkovTable.begin(), bind2nd(std::plus<int>(), 1)); 
        double logaritm = calculateLog(indxvalue    ,   sum_all_elements_vector(subvectorOfMarkovTable));
        this->mrkvTable.at(&*it)+=1;
        if(diff_indexes<=5){       
            data.amplitude.push_back(counter);
            data.self_compression.push_back(logaritm);
            data.normalized_compression.push_back(logaritm/normalization_base(diff_indexes, this->mrkvTable.alphSz));
        }
        else if (counter % division ==0){
            data.amplitude.push_back(counter);
            data.self_compression.push_back(logaritm);
            data.normalized_compression.push_back(logaritm/normalization_base(diff_indexes, this->mrkvTable.alphSz));
        }
    }
    return  data; 
}

/**
    Calculates the normalization_base by multiplying the number of elements in the input times the log_2 of the cardinality of the alphabet;
       
    @param std::vector<unsigned int>& subvector_markovtable. The reference to a sub vector of the input.
    @return void.
*/
double NormalizedCompressionMarkovTable::normalization_base(unsigned int length_of_tape, unsigned int cardinality){
   return ( length_of_tape * log2(cardinality) ); 
}

/**
    Sums all elements of the input vector;
       
    @param std::vector<unsigned int>& subvector_markovtable. The reference to a sub vector of the MarkovTable.
    @return int. sum of all vector elements
*/
int NormalizedCompressionMarkovTable::sum_all_elements_vector(std::vector<unsigned int>& subvector_markovtable)
{
    int sum_of_elems = 0;

    for (auto& n : subvector_markovtable){
        sum_of_elems += n;
        }
    
    // std::cout << "sum_all_line_elem = " << sum_of_elems << std::endl ;
    return sum_of_elems;
}

/**
    calculates the Logarithm of the ratio between two ints and returns a double;
    
    @param std::vector<unsigned int>& subvector_markovtable. The reference to a sub vector of the MarkovTable.
    @return double. Minus the log2 of the (index_value/sum_all_line_elem)/normalizer.
*/
double NormalizedCompressionMarkovTable::calculateLog(int index_value, int sum_all_line_elem){
    
    double value = static_cast<double>(index_value)/ static_cast<double>(sum_all_line_elem);
    //std::cout << "value div = " << value << std::endl;
    return (- DEFAULT_LOG2_LUT.log2(value));
}

void NormalizedCompressionMarkovTable::reset(){
    this->mrkvTable.reset();
}