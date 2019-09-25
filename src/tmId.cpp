#include "util.h"
#include "tmId.h"

#include <algorithm>    // std::find_if

std::ostream&
operator<<( std::ostream& dest, TmId value )
{
    std::ostream::sentry s( dest );
    if ( s ) {
        __uint128_t tmp = value;
        char buffer[ 128 ];
        char* d = std::end( buffer );
        do
        {
            -- d;
            *d = "0123456789"[ tmp % 10 ];
            tmp /= 10;
        } while ( tmp != 0 );
        int len = std::end( buffer ) - d;
        if ( dest.rdbuf()->sputn( d, len ) != len ) {
            dest.setstate( std::ios_base::badbit );
        }
    }
    return dest;
} 

TmId string_to_uint128(const std::string& s){
    if(s.empty()){
        throw std::runtime_error("input string is empty");
    }
    if(!is_number(s)){
      throw std::runtime_error("input string is not a number");
    }
    TmId number = 0;
    TmId base = 10;

    TmId exponent_value = s.size();
    for (auto l:s) {
        unsigned int a = l - '0';
        exponent_value-=1;
        number +=  a*ipow(base,exponent_value);

    }
    return number; 
}

bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}
