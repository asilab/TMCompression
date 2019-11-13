/**
    turingMachine.h
    Purpose: Create and execute Turing Machines.

    @author Jorge Miguel Ferreira da Silva
    @version 0.1
*/

#pragma once
#include <tuple>
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>

#include "traversal.h"
#include "tmId.h"
using Rng = std::minstd_rand;
using std::uniform_int_distribution;

using RecordId = unsigned int;
using State = unsigned int;
using Char = unsigned int;
using Move = unsigned int;

struct function_malfunction_exception: public std::exception {
    virtual const char* what() {
        return "error in function";
    }
};


struct TapeMoves{
  size_t previousValue;
  bool moveRight;
  bool moveLeft;
};

struct TuringRecord{
  Char write;
  Move move;
  State state;

  bool next(unsigned int number_of_states, unsigned int alphabet_size);
  std::string tr_to_string() const;
  static TuringRecord by_index(RecordId id, unsigned int number_of_states, unsigned int alphabet_size);
  bool operator<(const TuringRecord& tr) const;
  bool operator==(const TuringRecord& tr) const;
};

TuringRecord set_random(Rng rng, unsigned int number_of_states, unsigned int alphabet_size);
std::ostream& operator<<( std::ostream& o, const TuringRecord& r);

struct StateMatrix{
  std::vector<TuringRecord> v;
  unsigned int nbStates;
  unsigned int alphSz;

  StateMatrix(unsigned int number_of_states, unsigned int alphabet_size);

  void set_by_index(TmId id);
  void set_rule(unsigned int index, TuringRecord& tr);
  TmId calculate_index() const;
  std::string get_state_matrix_string();
  TuringRecord get_element(unsigned int index) const;
  unsigned int get_size()const;
  std::vector<TuringRecord> get_vector() const;
  /// Reset the state matrix into a uniformly random position.
  template<typename R>
  void set_random(R& rng) {
    auto write_dist = uniform_int_distribution<Char>(0, this->alphSz - 1);
    auto state_dist = uniform_int_distribution<State>(0, this->nbStates - 1);
    auto move_dist = uniform_int_distribution<Move>{0, 2};
    for (auto& st: this->v) {
      st.write = write_dist(rng);
      st.move = move_dist(rng);
      st.state = state_dist(rng);
    }
  }

  TuringRecord& at(Char alph, State state);
  const TuringRecord& at(Char alph, State state) const;
  bool next();
  void print() const;
  const TuringRecord* chr_line(Char c) const;
};

struct Tape {
  std::vector<Char> tape;
  size_t position;
  size_t max_size;
  size_t ind_left;
  size_t ind_right;

  Tape();

  Char getvalue();
  std::vector<unsigned int> get_written_tape() const;
  TapeMoves setandmove(Move relativePos, Char value);
  void resetTape();
  size_t getposition();
  void print() const;
  std::string print_written_tape(bool print_to_console) const;

  private:
    void reserve_right(size_t amount);
    void reserve_left(size_t amount);
};

std::ostream& operator<<( std::ostream& o, const Tape& t);

struct TuringMachine {
  State state;
  Tape turingTape;
  StateMatrix stMatrix;

  TuringMachine(unsigned int number_of_states, unsigned int alphabet_size);
  StateMatrix get_state_matrix() const;
  void reset_tape_and_state();
  std::vector<unsigned int> get_written_tape() const;
  std::string print_written_tape(bool print_to_console) const; 
  std::string print_written_tape_genomic_alphabet() const;
  TapeMoves act();
  void set_state_matrix(const StateMatrix& ruleMatrix);
  
};
