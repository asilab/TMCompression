#pragma once
#include <vector>

#include "traversal.h"

struct CompressionResultsData
{
  std::vector <unsigned int> amplitude;
  std::vector <double> normalized_compression;
  std::vector <double> self_compression;
};

/** Evaluate all relative turing machine programs with the given architecture.
 *
 * @param states
 * @param alphabet_size
 * @param num_iterations
 * @param k
 * @param strategy
 * @param verbose
 * @return a vector of normalized compression values, one per turing machine
 */
CompressionResultsData tm(
    size_t states,
    size_t alphabet_size,
    unsigned int num_iterations,
    unsigned int k,
    TraversalStrategy strategy = TraversalStrategy::SEQUENTIAL,
    unsigned long long traversal_len = 0,
    unsigned long long traversal_offset = 0,
    bool verbose = false);

void ktm(size_t states,
    size_t alphabet_size);