#ifndef INSTRUCTIONDEF_HH_
#define INSTRUCTIONDEF_HH_

#include <vector>
#include <string>
#include <bitset>
#include <functional>
#include "config.h"

class Computer;

struct InstructionDef
{
public:
    InstructionDef(std::string keyword_, size_t opCode_, std::function<void(Sequencer*,Computer&)> executor_, size_t operandCount_ = 0)
    : keyword(keyword_), opCode(opCode_), executor(executor_), operandCount(operandCount_)
    {}

    std::string keyword;
    bitset opCode;
    std::function<void(Sequencer*,Computer&)> executor;
    size_t operandCount;


    static const std::vector<InstructionDef> set;
};


#endif /* INSTRUCTION_HH_ */