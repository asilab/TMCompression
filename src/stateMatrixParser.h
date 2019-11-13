#pragma once
#include <string>
#include "turingMachine.h"

/// The RNG engine for sampling random numbers in Monte Carlo.
using Rng = std::minstd_rand;

bool is_string_char_number(const std::string& s);
StateMatrix string_to_state_matrix(std::string string_state_matrix, unsigned int number_of_states, unsigned int alphabet_size);
StateMatrix splitString(const std::string& str, int splitLength, unsigned int number_of_states, unsigned int alphabet_size);
std::vector<Metrics> mutate_state_matrix(std::string state_matrix_string,unsigned int states, unsigned int  alphabet_size,unsigned int numIt, bool print);
TuringRecord mutateRule(TuringRecord &rule);
std::vector<unsigned int> recreate_tm(StateMatrix stM, unsigned int states, unsigned int  alphabet_size, unsigned int numIt);
void test();
std::vector<Metrics> permutate_state_matrix(std::string state_matrix_string,unsigned int states, unsigned int  alphabet_size,unsigned int numIt, bool print );
std::pair<std::vector<unsigned int>,StateMatrix>random_tm(Rng rng, unsigned int states, unsigned int  alphabet_size, unsigned int numIt);
std::pair<std::vector<double>,StateMatrix> mutate_rules_once_at_a_time(StateMatrix stM, unsigned int states, unsigned int  alphabet_size, unsigned int numIt,
                                                                        BestKMarkovTables<NormalizedCompressionMarkovTable>& bestMkvTableCompression);
                                                                        
StateMatrix artificial_selection(std::pair<std::vector<double>,StateMatrix> state_matrix_pair_1,  
                                 std::pair<std::vector<double>,StateMatrix> state_matrix_pair_2);

bool machine_filter(StateMatrix state_matrix, unsigned int states,unsigned int alphabet_size, unsigned int numIt, unsigned int amplitude_criteria,
                    BestKMarkovTables<NormalizedCompressionMarkovTable>& bestMkvTableCompression);
void evolve_multiple_tms(unsigned int repeats, unsigned int number_of_tms,unsigned int states,unsigned int alphabet_size);
void evolve_multiple_tms2(unsigned int repeats , unsigned int number_of_iterations,unsigned int states,unsigned int alphabet_size);
Metrics real_nc_evolution(unsigned int number_tm_it,unsigned int tm_tape_iterations, unsigned int states, unsigned int alphabet_size, bool print);
Metrics avg_real_tm_nc_evolution(unsigned int number_tms, unsigned int tm_improve_repeats , unsigned int tm_iterations,unsigned int states,unsigned int alphabet_size);
void evolve_multiple_tms_graph(unsigned int max_number_tm_improve_repeats , unsigned int max_number_tm_tape_iterations, unsigned int states,unsigned int alphabet_size);