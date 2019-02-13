#pragma once
#include <vector>

#include "markovTable.h"

struct StringProcess{
    double normalizer;

    StringProcess();
    void normalization_base(std::vector<unsigned int> & vecOfStrs, size_t  &cardinality);
    double readinput(std::vector<unsigned int> & input, MarkovTable markovTable);
    int sum_all_elements_vector(std::vector<unsigned int>& subvector_markovtable);
    double calculateLog(int index_value, int sum_all_line_elem);
    void print() const;
};

bool getinputContent(std::vector<unsigned int> & intInputVector,size_t  &cardinality);
