#ifndef UTILS_HH_
#define UTILS_HH_

#include <sstream>
#include <string>
#include <ios>
#include <map>
#include "config.h"

#define HEX_DELIM 'x'
#define BIN_DELIM 'b'

struct BitsetHash {
  size_t operator()(const bitset& set) const
  {
      return set.to_string().size();
  }
};

enum Base {
    Bin,
    Oct,
    Hex,
    Dec,
    ASCII
};

long long int intFromString(std::string str);

std::string formatBinaryString(const std::string &str);

std::string bitsetToString(Base base, bitset set, bool addSpaces = false);

std::string baseToLabel(Base base);


#endif /* !UTILS_HH_ */