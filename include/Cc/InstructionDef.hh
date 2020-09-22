#ifndef INSTRUCTIONDEF_HH_
#define INSTRUCTIONDEF_HH_

#include <unordered_map>
#include <string>
#include <bitset>
#include "Computer/config.h"

struct InstructionDef
{
public:
    InstructionDef(std::string name_, wordSizeType code_, size_t operandCount_ = 0)
    : name(name_), code(code_),operandCount(operandCount_)
    {
    }

    std::string name;
    std::bitset<WORD_SIZE> code;
    wordSizeType operandSize;
    size_t operandCount;
};

#endif /* INSTRUCTION_HH_ */