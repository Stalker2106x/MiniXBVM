#ifndef CONFIG_H_
#define CONFIG_H_

#include <sul/dynamic_bitset.hpp>

#define OPCODE_BITSIZE 4

struct Config {
    Config() : byteSize(8), wordSize(16), dwordSize(32),
        ramAddrBitsize(4), ramDataBitsize(8)
    {};

    size_t byteSize;
    size_t wordSize;
    size_t dwordSize;

    size_t ramAddrBitsize; //Size of ram address
    size_t ramDataBitsize; //Size of ram value
};

typedef size_t wordSizeType; //Has to match bitset type... <size_t>

typedef sul::dynamic_bitset<> bitset;

#endif /* !CONFIG_H_ */