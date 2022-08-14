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
    Memory &ram = computer.getMemory(MemoryType::RAM);
    computer.getRegister(RegisterType::MemoryAdressRegistry).write(bitsetRange(computer.getOperandBitset(), 0, App::instance->config.ramAddrBitsize)); //Extract adress from Current RAM Block
    computer.getRegister(RegisterType::Accumulator).write(ram[computer.getRegister(RegisterType::MemoryAdressRegistry).read()].read());
}

void ADDExecutor(Computer &computer)
{
    Memory &ram = computer.getMemory(MemoryType::RAM);
    computer.getRegister(RegisterType::MemoryAdressRegistry).write(bitsetRange(computer.getOperandBitset(), 0, App::instance->config.ramAddrBitsize)); //Extract adress from Current RAM Block
    computer.getRegister(RegisterType::BRegister).write(ram[computer.getRegister(RegisterType::MemoryAdressRegistry).read()].read());
    computer.getRegister(RegisterType::Accumulator) += computer.getRegister(RegisterType::BRegister);
}

void SUBExecutor(Computer &computer)
{
    Memory &ram = computer.getMemory(MemoryType::RAM);
    computer.getRegister(RegisterType::MemoryAdressRegistry).write(bitsetRange(computer.getOperandBitset(), 0, App::instance->config.ramAddrBitsize)); //Extract adress from Current RAM Block
    computer.getRegister(RegisterType::BRegister).write(ram[computer.getRegister(RegisterType::MemoryAdressRegistry).read()].read());
    computer.getRegister(RegisterType::Accumulator) -= computer.getRegister(RegisterType::BRegister);
}

void MULExecutor(Computer &computer)
{
    Memory &ram = computer.getMemory(MemoryType::RAM);
    computer.getRegister(RegisterType::MemoryAdressRegistry).write(bitsetRange(computer.getOperandBitset(), 0, App::instance->config.ramAddrBitsize)); //Extract adress from Current RAM Block
    computer.getRegister(RegisterType::BRegister).write(ram[computer.getRegister(RegisterType::MemoryAdressRegistry).read()].read());
    computer.getRegister(RegisterType::Accumulator) *= computer.getRegister(RegisterType::BRegister);
}

void OUTExecutor(Computer &computer)
{
    computer.getRegister(RegisterType::Output).write(computer.getRegister(RegisterType::Accumulator).read()); //Extract acc to output
}

void HLTExecutor(Computer &computer)
{
    computer.halt();
}