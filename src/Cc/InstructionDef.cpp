#include "Cc/InstructionDef.hh"
#include "Computer/Computer.hh"
#include "bitset_utils.hh"
#include "App.hh"

InstructionDef::InstructionDef(std::string keyword_, unsigned long long code_, std::function<void(Computer&)> executor_, size_t operandCount_)
: keyword(keyword_), code(OPCODE_BITSIZE, code_), operandCount(operandCount_), executor(executor_)
{
}

size_t getInstructionSize(bitset opCode)
{
  auto defIt = std::find_if(instructionsSet.begin(), instructionsSet.end(), [&opCode] (InstructionDef def) { return (def.code == opCode); } );
  if (defIt == instructionsSet.end()) return (1); //Garbage, jump 1
  return (getInstructionSize(*defIt));
}

size_t getInstructionSize(const InstructionDef &instr)
{
  int instructionSize = (OPCODE_BITSIZE + (instr.operandCount * App::instance->config.ramAddrBitsize));
  return ((instructionSize / App::instance->config.ramDataBitsize) + ((instructionSize % App::instance->config.ramDataBitsize) == 0 ? 0 : 1));
}

void LDAExecutor(Computer &computer)
{
    computer._MAR.write(bitsetRange(computer.getOperandBitset(), 0, App::instance->config.ramAddrBitsize)); //Extract adress from Current RAM Block
    computer._accumulator.write(computer._RAM[computer._MAR.read()].read());
}

void ADDExecutor(Computer &computer)
{
    computer._MAR.write(bitsetRange(computer.getOperandBitset(), 0, App::instance->config.ramAddrBitsize)); //Extract adress from Current RAM Block
    computer._Breg.write(computer._RAM[computer._MAR.read()].read());
    computer._accumulator += computer._Breg;
}

void SUBExecutor(Computer &computer)
{
    computer._MAR.write(bitsetRange(computer.getOperandBitset(), 0, App::instance->config.ramAddrBitsize)); //Extract adress from Current RAM Block
    computer._Breg.write(computer._RAM[computer._MAR.read()].read());
    computer._accumulator -= computer._Breg;
}

void MULExecutor(Computer &computer)
{
    computer._MAR.write(bitsetRange(computer.getOperandBitset(), 0, App::instance->config.ramAddrBitsize)); //Extract adress from Current RAM Block
    computer._Breg.write(computer._RAM[computer._MAR.read()].read());
    computer._accumulator *= computer._Breg;
}

void OUTExecutor(Computer &computer)
{
    computer._output.write(computer._accumulator.read()); //Extract acc to output
}

void HLTExecutor(Computer &computer)
{
    computer.halt();
}