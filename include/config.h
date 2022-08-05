#ifndef CONFIG_H_
#define CONFIG_H_

#include <sul/dynamic_bitset.hpp>

const int WORD_SIZE = 4;
const int DWORD_SIZE = 4;
const int ADDRESS_SIZE = 4;

typedef size_t wordSizeType; //Has to match bitset type... <size_t>

typedef sul::dynamic_bitset<> bitset;

#endif /* !CONFIG_H_ */