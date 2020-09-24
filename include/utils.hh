#ifndef UTILS_HH_
#define UTILS_HH_

#include <string>
#include "config.h"

#define HEX_DELIM 'x'
#define BIN_DELIM 'b'

long long int int128FromString(std::string str);

template <wordSizeType WordSize>
std::string binStringFromInt128(long long int value)
{
    return (std::bitset<WordSize>(value).to_string());
}

#endif /* !UTILS_HH_ */