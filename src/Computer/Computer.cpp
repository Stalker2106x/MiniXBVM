#include <algorithm>
#include "Computer/Computer.hh"
#include "Cc/InstructionDef.hh"
#include "bitset_utils.hh"
#include "App.hh"

Computer::Computer() : bus(App::instance->config.ramDataBitsize, 0)
{
  _memories.emplace("RAM", Memory());
  _registers.emplace("ProgramCounter", Register(App::instance->config.ramAddrBitsize));
  _registers.emplace("MemoryAdressRegister", Register(App::instance->config.ramAddrBitsize));
  _registers.emplace("InstructionRegister", Register(App::instance->config.ramDataBitsize));
  _registers.emplace("Accumulator", Register(App::instance->config.ramDataBitsize));
  _registers.emplace("BRegister", Register(App::instance->config.ramDataBitsize));
  _registers.emplace("StatusRegister", Register(2));
  _registers.emplace("Output", Register(App::instance->config.ramDataBitsize));
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
  getRegister("ProgramCounter").write(bitset(App::instance->config.ramAddrBitsize, getMemory("RAM").getSize()-1));
  getRegister("MemoryAdressRegister").clear();
  getRegister("InstructionRegister").clear();
  getRegister("Accumulator").clear();
  getRegister("BRegister").clear();
  getRegister("Output").clear();
  getRegister("StatusRegister").clear();
  start();
}

void Computer::reset()
{
  getMemory("RAM").clear();
  restart();
}

Computer::State Computer::getState() const
{
  return (_state);
}

Memory &Computer::getMemory(const std::string &memType)
{
  try {
    return (_memories.at(memType));
  } catch (...) {
    throw std::runtime_error("Unknown memory type.");
  }
}

Register &Computer::getRegister(const std::string &regType)
{
  try {
    return (_registers.at(regType));
  } catch (...) {
    throw std::runtime_error("Unknown register type.");
  }
}

const Memory &Computer::getMemory(const std::string &memType) const
{
  try {
    return (_memories.at(memType));
  } catch (...) {
    throw std::runtime_error("Unknown memory type.");
  }
}

const Register &Computer::getRegister(const std::string &regType) const
{
  try {
    return (_registers.at(regType));
  } catch (...) {
    throw std::runtime_error("Unknown register type.");
  }
}

std::string Computer::dumpRegister(const std::string &regType, Base base) const
{
  return (bitsetToString(base, getRegister(regType).read(), true));
}

std::vector<std::pair<std::string, std::string>> Computer::dumpMemory(const std::string &memType, Base addrBase, Base valueBase) const
{
  auto dump = std::vector<std::pair<std::string, std::string>>();
  auto rawDump = getMemory(memType).read();
  bitset lastAddress = bitset(App::instance->config.ramAddrBitsize, getMemory("RAM").getSize()-1);

  for (bitset it = bitset(App::instance->config.ramAddrBitsize, 0); it < lastAddress; ++it)
  {
    dump.push_back(std::make_pair(bitsetToString(addrBase, it, true), bitsetToString(valueBase, rawDump.at(it).read(), true)));
  }
  return (dump);
}

std::string Computer::getOutput() const
{
  return (std::to_string(bitsetToLong(getRegister("Output").read())));
}

std::string Computer::getInstruction() const
{
  const bitset opCode = getRegister("InstructionRegister").read();
  auto defIt = std::find_if(instructionsSet.begin(), instructionsSet.end(), [&opCode] (InstructionDef def) { return (def.opCode == opCode); } );
  if (defIt != instructionsSet.end())
  {
    return (defIt->keyword);
  }
  return ("XXX");
}

std::string Computer::getFlags() const
{
  std::string res = "";
  auto state = getRegister("StatusRegister").read();
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
  bitset operand = bitsetRange(getMemory("RAM")[getRegister("MemoryAdressRegister").read()].read(), OPCODE_BITSIZE, App::instance->config.ramDataBitsize);
  size_t remainingBits = (App::instance->config.ramAddrBitsize - OPCODE_BITSIZE);
  size_t remainingBlocks = (remainingBits / App::instance->config.ramDataBitsize) + ((remainingBits % App::instance->config.ramDataBitsize) == 0 ? 0 : 1);
  for (size_t currentBlock = 1; currentBlock <= remainingBlocks; currentBlock++)
  {
    //One instruction + operands exceed one memory block, so we need to grab multiple
    operand = bitsetConcat(operand, getMemory("RAM")[getRegister("MemoryAdressRegister").read()+currentBlock].read());
  }
  return (operand);
}

void Computer::cycle(int deltaTime)
{
  if (_state != Running) return;
  if (clock.cycle(deltaTime))
  {
    sequencer.fetch();
    sequencer.execute(*this);
  }
}