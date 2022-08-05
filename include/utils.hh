#ifndef UTILS_HH_
#define UTILS_HH_

#include <sstream>
#include <string>
#include <ios>
#include "config.h"

#define HEX_DELIM 'x'
#define BIN_DELIM 'b'

enum Base {
    Bin,
    Oct,
    Hex,
    Dec
};

long long int int128FromString(std::string str);

std::string formatBinaryString(const std::string &str);

template <wordSizeType WordSize>
std::string bitsetToString(Base base, std::bitset<WordSize> bitset, bool addSpaces = false)
{
    std::stringstream ss;
    if (base == Base::Bin)
    {
        std::string str = bitset.to_string();
        for (int i = 0; i < str.size(); i++)
        {
            if (addSpaces && i % 8 == 0) ss << ' ';
            ss << str[i];
        }
    }
    else //Dec, Hex, Oct
    {
        if (base == Base::Hex) ss << std::hex;
        if (base == Base::Oct) ss << std::oct;
        ss << std::uppercase << bitset.to_ulong();
    }
    return (ss.str());
}


#endif /* !UTILS_HH_ */