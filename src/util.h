#pragma once
#include <stddef.h>


/**
    Returns int base raised to the power of an int exponent.

    @param base. int of the base.
    @param exp. int of the exponent.
    @return int base raised to the power of an int exponent.
*/
unsigned long long ipow(unsigned long long base, unsigned long long exp);

/** Calculate the full cardinality of all possible turing machine state matrices.
 * @param states the state cardinality
 * @param alphabet_size the alphabet's size
 */
unsigned long long tm_cardinality(size_t states, size_t alphabet_size);
