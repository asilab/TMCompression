/**
    util.cpp
    Purpose: Utility functions for the program.

    @author Jorge Miguel Ferreira da Silva
    @version 0.1
*/

#include <vector>
#include <iostream>

#include "util.h"

Log2Lut<double, 1000000> DEFAULT_LOG2_LUT {};

#define MAX 100000 

int multiply(int x, int res[], int res_size) { 
  int carry = 0; 
  for (int i = 0; i < res_size; i++) { 
      int prod = res[i] * x + carry; 
      res[i] = prod % 10; 
      carry = prod / 10; 
  } 
  
  while (carry) { 
      res[res_size] = carry % 10; 
      carry = carry / 10; 
      res_size++; 
  } 
return res_size; 
} 
  
// This function finds power of a number x 
void power(int x, int n)  
{
  if(n == 0 ){  
      std::cout<<"1"; 
      return; 
  }  
  int res[MAX]; 
  int res_size = 0; 
  int temp = x; 
  
  while (temp != 0) { 
      res[res_size++] = temp % 10; 
      temp = temp / 10; 
  } 
    
  for (int i = 2; i <= n; i++) 
      res_size = multiply(x, res, res_size); 

  for (int i = res_size - 1; i >= 0; i--) 
      std::cout << res[i]; 
} 

/// Calculate the full cardinality of all possible Turing machine state matrices
  void tm_fl_cardinality(size_t states, size_t alphabet_size) {
    
    int nstates = states;
    int  nalphabet = alphabet_size;
    auto record_cardinality = nstates * nalphabet * 3;
    power(record_cardinality, nstates * nalphabet);
}

/// Create the list of the number of machines with the growth of the number of states.
  void tm_growth_with_cardinality(size_t max_number_states){
    size_t min_number_states = 1;
    size_t alphabet_size=2;

    if (max_number_states< min_number_states){std::cerr<< "please insert number of states >= 1"<< std::endl; exit(0);}
     std::cout << "state" << "\t" <<"Number of Turing Machines"<< std::endl;

    for(auto state = min_number_states; state != max_number_states; ++state){
        std::cout << state << "\t"; 
        tm_fl_cardinality(state, alphabet_size);
        std::cout << std::endl;
    }
  }
  