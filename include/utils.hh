#ifndef UTILS_HH_
#define UTILS_HH_

#include <sstream>
#include <string>
#include <ios>
#include <iostream>
#include <map>
#include "config.h"

#define HEX_DELIM 'x'
#define BIN_DELIM 'b'

enum Base {
    Bin,
    Oct,
    Hex,
    Dec,
    ASCII
};

long long int int128FromString(std::string str);

std::string formatBinaryString(const std::string &str);

template <wordSizeType WordSize>
std::string bitsetToString(Base base, std::bitset<WordSize> bitset, bool addSpaces = false)
{
    if (base == Base::ASCII) return (std::string(1, static_cast<unsigned char>(bitset.to_ulong())));
    std::stringstream ss;
    if (base == Base::Bin)
    {
        std::string str = bitset.to_string();
        for (int i = 0; i < str.size(); i++)
        {
            if (addSpaces && i != 0 && (i % 8 == 0))
            {
                std::cout << "added at" << i << " for " << str;
                ss << ' ';
            }
            ss << str[i];
        }
    }
    else //Dec, Hex, Oct
    {
        if (base == Base::Hex) ss << "0x" << std::hex;
        if (base == Base::Oct) ss << "0" << std::oct;
        ss << std::uppercase << bitset.to_ulong();
    }
    return (ss.str());
}

std::string baseToLabel(Base base);


#endif /* !UTILS_HH_ */