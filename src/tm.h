#pragma once
#include <vector>

#include "traversal.h"
#include "markovTable.h"


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


/** Replicate experiment to determine the best k and it for a given number of states and alphabet size.
 *
 * @param states
 * @param alphabet_size
 */
void ktm(size_t states,
    size_t alphabet_size);

/** Evaluates a specific turing machine program.
 *
 * @param states
 * @param alphabet_size
 * @param num_iterations
 * @param k
 * @param tm_number
 */
 void tm_profile(
    size_t states,
    size_t alphabet_size,
    unsigned int num_iterations,
    unsigned int k,
    unsigned long int tm_number,
    unsigned int divison=5);


/** Evaluates a specific turing machine program dynamically,analysing the time complexity.
 * @param states
 * @param alphabet_size
 * @param num_iterations
 * @param k
 * @param tm_number
 */

 void tm_dynamical_profile(
    size_t states,
    size_t alphabet_size,
    unsigned int num_iterations,
    unsigned int k,
    unsigned long int tm_number,
    unsigned int divison=5);





/** Evaluate all relative turing machine programs with the given architecture,
 * using multiple threads.
 *
 * @param states
 * @param alphabet_size
 * @param num_iterations
 * @param k
 * @param strategy
 * @param verbose
 * @param threads the number of threads to run in parallel
 * @return a vector of normalized compression values, one per turing machine
 */
CompressionResultsData tm_multicore(
    size_t states,
    size_t alphabet_size,
    unsigned int num_iterations,
    unsigned int k,
    TraversalStrategy strategy = TraversalStrategy::SEQUENTIAL,
    unsigned long long traversal_len = 0,
    unsigned long long traversal_offset = 0,
    bool verbose = false,
    unsigned int threads = 2);

/** Replicate experiment to determine the best k and it for a given number of states and alphabet size with the given architecture,
 * using multiple threads.
 *
 * @param states
 * @param alphabet_size
 * @param threads the number of threads to run in parallel
 */
void ktm_multicore(
    size_t states,
    size_t alphabet_size,
    unsigned int threads);