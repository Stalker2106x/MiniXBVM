#include "Cc/InstructionDef.hh"
#include "Computer/Computer.hh"
#include "bitset_utils.hh"
#include "App.hh"

const std::vector<InstructionDef> InstructionDef::set = {
    {"NOP", 0, &Sequencer::NOPExecutor},
    {"LDA", 1, &Sequencer::LDAExecutor, 1},
    {"ADD", 2, &Sequencer::ADDExecutor, 1},
    {"SUB", 3, &Sequencer::SUBExecutor, 1},
    {"OUT", 5, &Sequencer::OUTExecutor},
    {"HLT", 6, &Sequencer::HLTExecutor}
};

InstructionDef::InstructionDef(std::string keyword_, size_t opCode_, Executor executor_, size_t operandCount_)
: keyword(keyword_), opCode(OPCODE_BITSIZE, opCode_), operandCount(operandCount_), executor(executor_)
{
}