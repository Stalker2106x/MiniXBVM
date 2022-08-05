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
    InstructionDef(std::string name_, wordSizeType code_, std::function<void(Computer&)> executor_, size_t operandCount_ = 0)
    : name(name_), code(code_), operandCount(operandCount_), executor(executor_)
    {
    }

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
    {"LDA", 0b0001, LDAExecutor, 1},
    {"ADD", 0b0010, ADDExecutor, 1},
    {"SUB", 0b0011, SUBExecutor, 1},
    {"MUL", 0b0100, MULExecutor, 1},
    {"OUT", 0b1110, OUTExecutor},
    {"HLT", 0b1111, HLTExecutor},
};

#endif /* INSTRUCTION_HH_ */