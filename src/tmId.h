#pragma once
#include <iostream>

#ifdef __SIZEOF_INT128__
    // do some fancy stuff here
    using TmId = __uint128_t;
    std::ostream& operator<<( std::ostream& dest, TmId value );
    TmId string_to_uint128(const std::string& s);
    bool is_number(const std::string& s);

#else
    # error This compiler does not support 128 bit integer types 
#endif

