/**
    markovTable.h
    Purpose: Make and fill Markov Tables.
             Measure Statistical Complexity.

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
    Acesses position on Markov Table, by providing a pointer to a position on array of unsigned int.

    @param const Char* characters.
    @return void.
*/
int& MarkovTable::at(const Char* characters){
    //std::cout << "str_to_index(characters) -> " << str_to_index(characters) << std::endl;
    //std::cout << "characters[k] -> " << characters[k]  << std::endl;
    //std::cout << "size = " << this->markovVector.size() << std::endl;
    return this->markovVector.at(( (str_to_index(characters) +1) * alphSz ) - (alphSz - characters[k]) ); 
}

/**
    Provides line of of Markov Table, by providing a pointer to a position on array of unsigned ints.

    @param const Char* characters.
    @return vector of unsigned ints.
*/
std::vector<unsigned int> MarkovTable::getLine(const Char* characters) const{
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
size_t MarkovTable::str_to_index(const Char* x)  const{
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