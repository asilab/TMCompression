/**
    stringProcess.cpp
    Purpose: Read Input String and evaluate Compression Capability of Turing machine.

    @author Jorge Miguel Ferreira da Silva
    @version 0.1
*/

//Includes
#include <math.h>
#include <map>

#include "stringProcess.h"

//------------------------------------


/** StringProcess Struct

    StringProcess Struct. Struct that reads input and evaluate Compression Capability of Turing machine.
*/
StringProcess::StringProcess():
 normalizer(0) {}

/**
    Calculates the normalization_base by multiplying the number of elements in the input times the log_2 of the cardinality of the alphabet;
       
    @param std::vector<unsigned int>& subvector_markovtable. The reference to a sub vector of the input.
    @return void.
*/
void StringProcess::normalization_base(std::vector<unsigned int> & vecOfStrs, size_t &cardinality){
   if (cardinality<0)
    {
        std::cerr << "Cardinality of string error " << std::endl;
        exit(0);
    }

   this->normalizer = vecOfStrs.size() * log2(cardinality);
}

/**
    Reads each element of the input vector and using the Markov table executes the folowing steps:
    - For each element of the input in the context k it gets the value in the MarkovTable (function markovTable.at) and adds +1;
    - Gets the line of the MarkovTable for the specified context (markovTable.getLine) and adds to the vector +1 in each element;
    - Using this it calculates the sum of all elements of the line (sum_all_elements_vector)
    - And with the input value at the table and the sum of all elements of the line it determines log2 (calculateLog)
    - Adds the value to the compression variable.

    @param std::vector<unsigned int>& input. The reference to an input vector of the input string.
    @param MarkovTable. Markov Table of computed values.
    @return void.
*/
double StringProcess::readinput(std::vector<unsigned int>& input, MarkovTable markovTable){
    auto it = input.begin();
    auto end = input.end() - markovTable.k;
    unsigned int value = 0 ;

    // std::cout<<"---------------------------------- "<< std::endl;
    // for(auto it = input.begin(); it!= input.end(); ++it){
    // std::cout<<" "<<*it;}
    // std::cout<< std::endl;
    // std::cout<<"---------------------------------- "<< std::endl;

    for(auto it = input.begin(); it!= input.end() - markovTable.k; ++it){
        
        //markovTable.print();
        //std::cout<<"input index --> "<<*it<< std::endl;
        auto subvectorOfMarkovTable = markovTable.getLine(&*it); 
        auto indxvalue = markovTable.at(&*it) + 1;
        std::transform(subvectorOfMarkovTable.begin(), subvectorOfMarkovTable.end(), subvectorOfMarkovTable.begin(), bind2nd(std::plus<int>(), 1)); 
        //std::cout << "value on the table = " << indxvalue << std::endl ;
        //markovTable.print();   
        // for (auto i = subvectorOfMarkovTable.begin(); i != subvectorOfMarkovTable.end(); ++i)
        // std::cout << *i << ' ';
        // std::cout << std::endl;

        auto logaritm = calculateLog(indxvalue    ,   sum_all_elements_vector(subvectorOfMarkovTable));
        value += logaritm;
        
    }
    // std::cout << "value = " << value << std::endl ;
    // std::cout << "Normalizer of the String = " << this->normalizer << std::endl;

    return (value/this->normalizer);
}


/**
    Sums all elements of the input vector;
       
    @param std::vector<unsigned int>& subvector_markovtable. The reference to a sub vector of the MarkovTable.
    @return int. sum of all vector elements
*/
int StringProcess::sum_all_elements_vector(std::vector<unsigned int>& subvector_markovtable)
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
double StringProcess::calculateLog(int index_value, int sum_all_line_elem){
    
    auto value = static_cast<double>(index_value)/ static_cast<double>(sum_all_line_elem);
    // std::cout << "value div = " << value << std::endl ;
    return (- log2(value));
}


/**
    Prints the compression variable of the Struct StringProcess       
    @return void.
*/
void StringProcess::print() const{
    std::cout << "Normalizer of the String = " << this->normalizer << std::endl;
}



bool getinputContent(std::vector<unsigned int> & intInputVector, size_t &cardinality)
{
  std::string str;
  int counter = -1;
  std::map<char, unsigned int> mapping;
  while (std::getline(std::cin, str)){ 
    if(str.size() > 0){

      for (auto it=str.begin(); it!=str.end(); ++it){
        if ( mapping.find(*it) == mapping.end()){
          mapping[*it] = ++counter;
          intInputVector.push_back(counter);
        }
        else{intInputVector.push_back(mapping.find(*it)->second);}           
      }
    }
  }
    cardinality = mapping.size();
  if (intInputVector.size()==0){
    std::cerr << "Empty input received" << std::endl;
    return false;
  }
  return true;
}