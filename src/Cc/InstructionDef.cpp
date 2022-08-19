#include "Cc/InstructionDef.hh"
#include "Computer/Computer.hh"
#include "bitset_utils.hh"
#include "App.hh"

InstructionDef::InstructionDef(std::string keyword_, size_t opCode_, std::function<void(Computer&)> executor_, size_t operandCount_)
: keyword(keyword_), opCode(OPCODE_BITSIZE, opCode_), operandCount(operandCount_), executor(executor_)
{
}

void InstructionDef::init()
{
    const Computer &computer = *App::instance->computer;
    const Sequencer &sequencer = computer.sequencer;
    instructionsSet = {
        {"NOP", 0, std::bind(&Sequencer::NOPExecutor, sequencer, computer)},
        {"LDA", 1, std::bind(&Sequencer::LDAExecutor, sequencer, computer), 1},
        {"ADD", 2, std::bind(&Sequencer::ADDExecutor, sequencer, computer), 1},
        {"SUB", 3, std::bind(&Sequencer::SUBExecutor, sequencer, computer), 1},
        {"OUT", 5, std::bind(&Sequencer::OUTExecutor, sequencer, computer)},
        {"HLT", 6, std::bind(&Sequencer::HLTExecutor, sequencer, computer)}
    };
}