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
    InstructionDef(std::string keyword_, unsigned long long code_, std::function<void(Computer&)> executor_, size_t operandCount_ = 0);

    std::string keyword;
    bitset code;
    std::function<void(Computer&)> executor;
    size_t operandCount;
};
//EXECUTORS
void LDAExecutor(Computer &computer);
void ADDExecutor(Computer &computer);
void SUBExecutor(Computer &computer);
void MULExecutor(Computer &computer);
void OUTExecutor(Computer &computer);
void HLTExecutor(Computer &computer);

const std::vector<InstructionDef> instructionsSet = {
    {"LDA", 1, LDAExecutor, 1},
    {"ADD", 2, ADDExecutor, 1},
    {"SUB", 3, SUBExecutor, 1},
    {"MUL", 4, MULExecutor, 1},
    {"OUT", 5, OUTExecutor},
    {"HLT", 6, HLTExecutor}
};

#endif /* INSTRUCTION_HH_ */