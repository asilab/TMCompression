/**
    markovTable.h
    Purpose: Make and fill Markov Tables.
             Mesure Statistical Complexity.

    @author Jorge Miguel Ferreira da Silva
    @version 0.1
*/
#include <math.h>

#include "markovTable.h"
#include "util.h"

/**MarkovTable Struct*/

/**
    MarkovTable Struct. Table of repetitions a given contex has for a given alphabet.
    Example:
    k/context=2, alphabet size=2,  string = -010110011-

    __|_0_|_1_
    00| 0 | 1
    01| 1 | 2
    10| 1 | 1
    11| 1 | 0

    Note: All this is mapped into a vector of integers.
    @param k. Size of context to consider on the MarkovTable.
    @param alphabet_size. Size of the alphabet being considered by the tm.
*/
MarkovTable::MarkovTable(unsigned int k, unsigned int alphabet_size):
  markovVector(alphabet_size* ipow(alphabet_size,k),0), alphSz(alphabet_size), k(k){}

/**
    Acesses position on Markov Table, by providing a pointer to a position on array of chars.

    @param void.
    @return void.
*/
int& MarkovTable::at(const Char* characters){
    // std::cout<< "str_to_index(characters) -> " << str_to_index(characters) << std::endl;
    // std::cout<< "characters[k] -> " << characters[k]  << std::endl;
    return this->markovVector.at(( (str_to_index(characters) +1) * alphSz ) - (alphSz - characters[k]) ); 
}

std::vector<unsigned int> MarkovTable::getLine(const Char* characters){
    // std::cout<< "characters -> "<< *characters << std::endl;
    // std::cout<< "str_to_index(characters) -> " << str_to_index(characters) << std::endl;
    // std::cout<<"Begin --> " <<(((str_to_index(characters) + 1) * this->alphSz) - this->alphSz)<< std::endl;
    // std::cout<<"End --> " << (    (str_to_index(characters) + 1) * this->alphSz   ) << std::endl;

    auto it_begin = this->markovVector.begin() + (  (   (str_to_index(characters) + 1) * this->alphSz   ) - this->alphSz    );
    auto it_end = this->markovVector.begin() + (    (str_to_index(characters) + 1) * this->alphSz   );
    std::vector <unsigned int> newVec(it_begin,it_end);

    return newVec;
}




/**
    Resets Markov Table.

    @param void.
    @return void.
*/
void MarkovTable::reset() {
    std::fill(this->markovVector.begin(), this->markovVector.end(), 0);
}


/**
    Takes in pointer to char array and returns the context number on the Markov Table.

    @param const Char*. Pointer to char array.
    @return size_t. Returns context number on the Markov Table.
*/
size_t MarkovTable::str_to_index(const Char* x) {
    size_t o = 0;
    for (auto i = 0u; i < this->k; ++i) { //-1
        o = (o * this->alphSz) + x[i];
    }
    return o;
}

/**
    Prints Markov Table.

    @param void.
    @return void.
*/
void MarkovTable::print() const{
    unsigned int counter = 0;
    std::cout << std::endl;
    std::cout << "Markov Table" << std::endl;
    for(auto&& x: this->markovVector){
        std::cout << x  << "\t";
        if(++counter == this->alphSz){
            std::cout << std::endl;
            counter = 0;
        }
    }
    std::cout << std::endl;
}


NormalizedCompressionMarkovTable::NormalizedCompressionMarkovTable(unsigned int k, unsigned int alphabet_size):
mrkvTable(k, alphabet_size) {}

Metrics NormalizedCompressionMarkovTable::update_nc_mk_table(const Tape& tape){
    auto b = begin(tape.tape) + tape.ind_left - this->mrkvTable.k  + 1 ; // To have k context at the begining    
    auto e = begin(tape.tape) + tape.ind_right - this->mrkvTable.k;
    Metrics metrics;


    double value = 0 ;

    for (auto it = b; it != e; ++it) {
        auto indxvalue = this->mrkvTable.at(&*it) + 1;
        auto subvectorOfMarkovTable = this->mrkvTable.getLine(&*it); 
        
        std::transform(subvectorOfMarkovTable.begin(), subvectorOfMarkovTable.end(), subvectorOfMarkovTable.begin(), bind2nd(std::plus<int>(), 1)); 
        double logaritm = calculateLog(indxvalue    ,   sum_all_elements_vector(subvectorOfMarkovTable));
        value += logaritm;
        this->mrkvTable.at(&*it)+=1;
    }
    
    metrics.selfCompression = value;
    unsigned int diff_indexes = (tape.ind_right) - (tape.ind_left + 1);
    metrics.amplitude = diff_indexes;
    metrics.normalizedCompression = (value/normalization_base(diff_indexes, this->mrkvTable.alphSz));
    return  metrics; 
}

//obtain all values of specific table
CompressionResultsData NormalizedCompressionMarkovTable::profile_update_nc_mk_table(const Tape& tape, unsigned int divison){
    auto b = begin(tape.tape) + tape.ind_left- this->mrkvTable.k  + 1 ; // To have k context at the begining    
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
        else if (counter % divison ==0){
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
    //std::cout << "value div = " << value << std::endl ;
    return (- log2(value));
}