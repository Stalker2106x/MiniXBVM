#include <algorithm>
#include "Computer/Computer.hh"
#include "Cc/InstructionDef.hh"
#include "bitset_utils.hh"
#include "App.hh"

Computer::Computer()
{
  _memories.emplace(MemoryType::RAM, Memory());
  _registers.emplace(RegisterType::ProgramCounter, Register(App::instance->config.ramAddrBitsize));
  _registers.emplace(RegisterType::MemoryAdressRegistry, Register(App::instance->config.ramAddrBitsize));
  _registers.emplace(RegisterType::InstructionRegister, Register(OPCODE_BITSIZE));
  _registers.emplace(RegisterType::Accumulator, Register(App::instance->config.ramDataBitsize));
  _registers.emplace(RegisterType::BRegister, Register(App::instance->config.ramDataBitsize));
  _registers.emplace(RegisterType::StatusRegister, Register(2));
  _registers.emplace(RegisterType::Output, Register(App::instance->config.ramDataBitsize));
  restart();
}

void Computer::start()
{
  _state = Running;
  clock.reset();
}

void Computer::halt()
{
  _state = Off;
  clock.setState(Clock::State::Paused);
}

void Computer::restart()
{
  getRegister(RegisterType::ProgramCounter).write(bitset(App::instance->config.ramAddrBitsize, getMemory(MemoryType::RAM).getSize()-1));
  getRegister(RegisterType::MemoryAdressRegistry).clear();
  getRegister(RegisterType::InstructionRegister).clear();
  getRegister(RegisterType::Accumulator).clear();
  getRegister(RegisterType::BRegister).clear();
  getRegister(RegisterType::Output).clear();
  getRegister(RegisterType::StatusRegister).clear();
  start();
}

void Computer::reset()
{
  getMemory(MemoryType::RAM).clear();
  restart();
}

Computer::State Computer::getState() const
{
  return (_state);
}

Memory &Computer::getMemory(MemoryType memType)
{
  try {
    return (_memories.at(memType));
  } catch (...) {
    throw std::runtime_error("Unknown memory type.");
  }
}

Register &Computer::getRegister(RegisterType regType)
{
  try {
    return (_registers.at(regType));
  } catch (...) {
    throw std::runtime_error("Unknown register type.");
  }
}

const Memory &Computer::getMemory(MemoryType memType) const
{
  try {
    return (_memories.at(memType));
  } catch (...) {
    throw std::runtime_error("Unknown memory type.");
  }
}

const Register &Computer::getRegister(RegisterType regType) const
{
  try {
    return (_registers.at(regType));
  } catch (...) {
    throw std::runtime_error("Unknown register type.");
  }
}

std::string Computer::dumpRegister(RegisterType regType, Base base) const
{
  auto dump = std::string();
  switch (regType)
  {
    case ProgramCounter:
      dump = bitsetToString(base, getRegister(RegisterType::ProgramCounter).read(), true);
      break;
    case MemoryAdressRegistry:
      dump = bitsetToString(base, getRegister(RegisterType::MemoryAdressRegistry).read(), true);
      break;
    case InstructionRegister:
      dump = bitsetToString(base, getRegister(RegisterType::InstructionRegister).read(), true);
      break;
    case Accumulator:
      dump = bitsetToString(base, getRegister(RegisterType::Accumulator).read(), true);
      break;
    case BRegister:
      dump = bitsetToString(base, getRegister(RegisterType::BRegister).read(), true);
      break;
    case Output:
      dump = bitsetToString(base, getRegister(RegisterType::Output).read(), true);
      break;
    case StatusRegister:
      dump = bitsetToString(base, getRegister(RegisterType::StatusRegister).read(), true);
      break;
  }
  return (dump);
}

std::vector<std::pair<std::string, std::string>> Computer::dumpMemory(MemoryType memType, Base addrBase, Base valueBase) const
{
  auto dump = std::vector<std::pair<std::string, std::string>>();
  switch (memType)
  {
    case RAM:
      auto rawDump = getMemory(MemoryType::RAM).read();
      bitset lastAddress = bitset(App::instance->config.ramAddrBitsize, getMemory(MemoryType::RAM).getSize()-1);

      for (bitset it = bitset(App::instance->config.ramAddrBitsize, 0); it < lastAddress; ++it)
      {
        dump.push_back(std::make_pair(bitsetToString(addrBase, it, true), bitsetToString(valueBase, rawDump.at(it).read(), true)));
      }
      break;
  }
  return (dump);
}

std::string Computer::getOutput() const
{
  return (std::to_string(bitsetToLong(getRegister(RegisterType::Output).read())));
}

std::string Computer::getInstruction() const
{
  const bitset opCode = getRegister(RegisterType::InstructionRegister).read();
  auto defIt = std::find_if(instructionsSet.begin(), instructionsSet.end(), [&opCode] (InstructionDef def) { return (def.code == opCode); } );
  if (defIt != instructionsSet.end())
  {
    return (defIt->keyword);
  }
  return ("XXX");
}

std::string Computer::getFlags() const
{
  std::string res = "";
  auto state = getRegister(RegisterType::StatusRegister).read();
  if (state[0] == 1)
    res += "CY";
  else
    res += "--";
  if (state[1] == 1)
    res += "ZR";
  else
    res += "--";
  return (res);
}

bitset Computer::getOperandBitset() const
{
  bitset operand = bitsetRange(getMemory(MemoryType::RAM)[getRegister(RegisterType::MemoryAdressRegistry).read()].read(), OPCODE_BITSIZE, App::instance->config.ramDataBitsize);
  size_t remainingBits = (App::instance->config.ramAddrBitsize - OPCODE_BITSIZE);
  size_t remainingBlocks = (remainingBits / App::instance->config.ramDataBitsize) + ((remainingBits % App::instance->config.ramDataBitsize) == 0 ? 0 : 1);
  for (size_t currentBlock = 1; currentBlock <= remainingBlocks; currentBlock++)
  {
    //One instruction + operands exceed one memory block, so we need to grab multiple
    operand = bitsetConcat(operand, getMemory(MemoryType::RAM)[getRegister(RegisterType::MemoryAdressRegistry).read()+currentBlock].read());
  }
  return (operand);
}

void Computer::cycle(int deltaTime)
{
  if (_state != Running) return;
  if (clock.cycle(deltaTime))
  {
    getRegister(RegisterType::ProgramCounter) += getInstructionSize(getRegister(RegisterType::InstructionRegister).read());
    getRegister(RegisterType::MemoryAdressRegistry) = getRegister(RegisterType::ProgramCounter);
    const bitset opCode = bitsetRange(getMemory(MemoryType::RAM)[getRegister(RegisterType::MemoryAdressRegistry).read()].read(), 0, OPCODE_BITSIZE);
    getRegister(RegisterType::InstructionRegister).write(opCode); //Read the current instruction and store it in instruction registr
    auto defIt = std::find_if(instructionsSet.begin(), instructionsSet.end(), [&opCode] (InstructionDef def) { return (def.code == opCode); } );
    if (defIt != instructionsSet.end())
    {
      defIt->executor(*this);
    }
  }
}