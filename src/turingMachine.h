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

using std::uniform_int_distribution;

using RecordId = unsigned int;
using State = unsigned int;
using Char = unsigned int;
using Move = unsigned int;

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

  static TuringRecord by_index(RecordId id, unsigned int number_of_states, unsigned int alphabet_size);
};

std::ostream& operator<<( std::ostream& o, const TuringRecord& r);

struct StateMatrix{
  std::vector<TuringRecord> v;
  unsigned int nbStates;
  unsigned int alphSz;

  StateMatrix(unsigned int number_of_states, unsigned int alphabet_size);

  void set_by_index(TmId id);
  TmId calculate_index() const;

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
  TapeMoves setandmove(Move relativePos, Char value);
  void resetTape();
  size_t getposition();
  void print() const;
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
  void reset_tape_and_state();
  TapeMoves act();
};
