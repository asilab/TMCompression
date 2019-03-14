/**
    tm.h
    Purpose: Various functions related to:
    - Profile of TM
    - Dynamical Profile of TM
    - Test various k
    - Mutithread TM
    - Cardinality of TM

    @author Jorge Miguel Ferreira da Silva
    @version 0.1
*/

#pragma once
#include <vector>

#include "traversal.h"
#include "markovTable.h"


/** Evaluate all relative Turing machine programs with the given architecture.
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
    std::vector <unsigned int> kvector,
    TraversalStrategy strategy = TraversalStrategy::SEQUENTIAL,
    unsigned long long traversal_len = 0,
    unsigned long long traversal_offset = 0,
    bool verbose = false);


/** Replicate experiment to determine the best k and it for a given number of states and alphabet size.
 *
 * @param states
 * @param alphabet_size
 */
void ktm(size_t states, size_t alphabet_size);

/** Prints a specific Turing machine tape after a given number of iterations.
 *
 * @param states
 * @param alphabet_size
 * @param num_iterations
 * @param tm_number
 */
void tm_print_tape(
    size_t states,
    size_t alphabet_size,
    unsigned int num_iterations,
    TmId tm_number);

/**Print State matrix of a Turing machine
 * 
 * @param states
 * @param alphabet_size
 * @param tm_number
 */

void tm_print_state_matrix(
  size_t states,
  size_t alphabet_size,
  TmId tm_number);


/** Evaluates a specific Turing machine Profile.
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
    TmId tm_number,
    unsigned int divison=5);


/** Evaluates a specific Turing machine program dynamically,analysing the time complexity.
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
    TmId tm_number,
    unsigned int divison=5);


/** Evaluate all relative Turing machine programs with the given architecture,
 * using multiple threads.
 *
 * @param states
 * @param alphabet_size
 * @param num_iterations
 * @param k
 * @param strategy
 * @param verbose
 * @param threads the number of threads to run in parallel
 * @return a vector of normalized compression values, one per Turing machine
 */
CompressionResultsData tm_multicore(
    size_t states,
    size_t alphabet_size,
    unsigned int num_iterations,
    std::vector<unsigned int> kvector,
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