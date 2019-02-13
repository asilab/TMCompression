#pragma once
#include <tuple>
#include <vector>
#include <iostream>
#include <algorithm>

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

  bool next(size_t number_of_states, size_t alphabeth_size);
};

std::ostream& operator<<( std::ostream& o, const TuringRecord& r);

struct StateMatrix{
  std::vector<TuringRecord> v;
  size_t nbStates;
  size_t alphSz;

  StateMatrix(size_t number_of_states, size_t alphabeth_size);

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
  TapeMoves moveandSet(Move relativePos, Char value);
  void resetTape();
  size_t getposition();

  private:
    void reserve_right(size_t amount);
    void reserve_left(size_t amount);
};

std::ostream& operator<<( std::ostream& o, const Tape& t);

struct TuringMachine {
  State state;
  Tape turingTape;
  StateMatrix stMatrix;

  TuringMachine(size_t number_of_states, size_t alphabeth_size);
  void reset();
  TapeMoves act();
};

