#pragma once
#include <iostream>

using TmId = __uint128_t;
std::ostream& operator<<( std::ostream& dest, TmId value );