#pragma once
#include <iostream>

using TmId = __uint128_t;
std::ostream& operator<<( std::ostream& dest, TmId value );
TmId string_to_uint128(std::string& s);
bool is_number(const std::string& s);
