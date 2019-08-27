#pragma once
#include <vector>

#include "metrics.h"

std::vector<unsigned int> edit_vector(double mutationRate, 
                                        std::vector<unsigned int>& input_vector, 
                                        unsigned int cardinality_value,
                                        bool natural_sequence);


//read and process virus:
std::pair<std::vector<unsigned int>,unsigned int> read_virus_file(std::string virus_path);
std::pair<std::vector<unsigned int>,unsigned int>  getinputContent(const std::string& str);

//permutate sequence:
std::vector <std::vector <unsigned int>> permutate_vector(const std::vector <unsigned int>& edited_vector, const unsigned int& add_value);
std::vector <std::vector <unsigned int>> divide_to_chunks_vector(const std::vector <unsigned int>& edited_vector, unsigned int& divisions);
std::vector <unsigned int> shuffle_vector(const std::vector <std::vector <unsigned int>> chunked_vector);
//nc calc:
void nc_substitution_permutate_sequence(bool natural_sequence, std::string virus_path);
