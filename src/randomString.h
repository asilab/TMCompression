#pragma once
#include <vector>

#include "metrics.h"

std::vector<unsigned int> mutate_vector(double mutationRate, std::vector<unsigned int>& input_vector, unsigned int cardinality_value);
void nc_mutated_string(size_t alphabet_size);