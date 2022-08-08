#ifndef CONFIG_H_
#define CONFIG_H_

#include <sul/dynamic_bitset.hpp>

#define OPCODE_BITSIZE 4

struct Config {
    Config() : byteSize(8), wordSize(16), dwordSize(32),
        ramAddrBitsize(4), ramDataBitsize(8)
    {};

    const size_t byteSize;
    const size_t wordSize;
    const size_t dwordSize;

    const size_t ramAddrBitsize; //Size of ram address
    const size_t ramDataBitsize; //Size of ram value
};

typedef size_t wordSizeType; //Has to match bitset type... <size_t>

typedef sul::dynamic_bitset<> bitset;

#endif /* !CONFIG_H_ */