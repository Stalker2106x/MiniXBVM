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
    InstructionDef(std::string keyword_, size_t opCode_, std::function<void(Computer&)> executor_, size_t operandCount_ = 0);

    static void init();

    std::string keyword;
    bitset opCode;
    std::function<void(Computer&)> executor;
    size_t operandCount;
};

static std::vector<InstructionDef> instructionsSet;

//Util
//size_t getInstructionSize(bitset opCode);
//size_t getInstructionSize(const InstructionDef &keyword);

#endif /* INSTRUCTION_HH_ */