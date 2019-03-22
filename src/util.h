/**
    util.h
    Purpose: Utility functions for the program.

    @author Jorge Miguel Ferreira da Silva
    @version 0.1
*/

#pragma once
#include <stddef.h>
#include <array>
#include <cmath>

/**
    Returns integer base raised to the power of an integer exponent.

    @param base. int of the base.
    @param exp. int of the exponent.
    @return int base raised to the power of an int exponent.
*/
template <typename T>
T ipow(T base, T exp) {
    if (exp == 0) {
      return 1;
    }
    if (exp == 1) {
      return base;
    }
    T result = 1;
    for (;;)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        if (!exp)
            break;
        base *= base;
    }
    return result;
}

/** Calculate the number of Turing machines with the increase in number of states.
 * @param max_number_states the number of states cardinality
 */
void tm_growth_with_cardinality(size_t max_number_states);


void tm_fl_cardinality(size_t states, size_t alphabet_size);


// This function finds power of a number x 
void power(int x, int n);

/* This function multiplies x  with the number represented by res[]. 
 res_size is size of res[] or number of digits in the number represented by res[]. This function uses simple school mathematics for multiplication. 
This function may value of res_size and returns the new value of res_size */
int multiply(int x, int res[], int res_size);

/// Look-up table for log2
template <typename T, size_t precision>
class Log2Lut {
    std::array<T, precision> lut;
    T m;

    public:
    Log2Lut()
    : m(precision)
    {
        for (size_t i = 1; i <= precision; i++) {
            T x = i;
            x /= this->m;
            this->lut[i] = std::log2(x);
        }
    }

    T log2(T x) const {
        return this->lut.at(static_cast<size_t>(x * m ) - 1);
    }
};

extern Log2Lut<double, 1000> DEFAULT_LOG2_LUT;
