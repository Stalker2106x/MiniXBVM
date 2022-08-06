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
    InstructionDef(std::string name_, unsigned long long code_, std::function<void(Computer&)> executor_, size_t operandCount_ = 0);

    std::string name;
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
    {"LDA", 0, LDAExecutor, 1},
    {"ADD", 1, ADDExecutor, 1},
    {"SUB", 2, SUBExecutor, 1},
    {"MUL", 3, MULExecutor, 1},
    {"OUT", 4, OUTExecutor},
    {"HLT", 5, HLTExecutor},
};

#endif /* INSTRUCTION_HH_ */