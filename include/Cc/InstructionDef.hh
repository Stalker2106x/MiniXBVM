#ifndef INSTRUCTIONDEF_HH_
#define INSTRUCTIONDEF_HH_

#include <vector>
#include <string>
#include <bitset>
#include <functional>
#include "config.h"

class Computer;
class Sequencer;

typedef void (Sequencer::*Executor)(Computer&);

struct InstructionDef
{
public:
    InstructionDef(std::string keyword_, size_t opCode_, Executor executor_, size_t operandCount_ = 0);

    static const std::vector<InstructionDef> set;

    std::string keyword;
    bitset opCode;
    Executor executor;
    size_t operandCount;
};


//Util
//size_t getInstructionSize(bitset opCode);
//size_t getInstructionSize(const InstructionDef &keyword);

#endif /* INSTRUCTION_HH_ */