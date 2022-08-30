#ifndef UTILS_HH_
#define UTILS_HH_

#include <sul/dynamic_bitset.hpp>
#include <string>
#include "config.h"

#define HEX_DELIM 'x'
#define BIN_DELIM 'b'

struct BitsetHash {
  size_t operator()(const bitset& set) const
  {
      return set.to_string().size();
  }
};

struct not_alphanumeric {
    bool operator()(char c) {
        return (!std::isalpha(c) && !std::isdigit(c));
    }
};

struct not_binary {
    bool operator()(char c) {
        return (std::string("01").find(c) == std::string::npos);
    }
};

struct not_octal {
    bool operator()(char c) {
        return (std::string("01234567").find(c) == std::string::npos);
    }
};

struct not_decimal {
    bool operator()(char c) {
        return (std::string("0123456789").find(c) == std::string::npos);
    }
};

struct not_hexadecimal {
    bool operator()(char c) {
        return (std::string("0123456789ABCDEF").find(c) == std::string::npos);
    }
};

enum Base {
    Unknown,
    Bin,
    Oct,
    Hex,
    Dec,
    ASCII
};

long long int intFromString(Base stringBase, std::string str);

std::string formatBinaryString(const std::string &str);

long long int bitsetToLong(bitset set);

std::string bitsetToString(Base base, bitset set, bool addSpaces = false);

std::string baseToLabel(Base base);


#endif /* !UTILS_HH_ */