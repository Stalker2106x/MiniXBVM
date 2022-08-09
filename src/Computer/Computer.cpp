#include <algorithm>
#include "Computer/Computer.hh"
#include "Cc/InstructionDef.hh"
#include "bitset_utils.hh"
#include "App.hh"

Computer::Computer()
  : _RAM(), _PC(App::instance->config.ramAddrBitsize), _MAR(App::instance->config.ramAddrBitsize), _IR(OPCODE_BITSIZE),
    _accumulator(App::instance->config.ramDataBitsize), _Breg(App::instance->config.ramDataBitsize), _SR(2), _output(App::instance->config.ramDataBitsize)
{
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
  _PC.write(bitset(App::instance->config.ramAddrBitsize, _RAM.getSize()-1));
  _MAR.clear();
  _IR.clear();
  _accumulator.clear();
  _Breg.clear();
  _output.clear();
  _SR.clear();
  start();
}

void Computer::reset()
{
  _RAM.clear();
  restart();
}

void Computer::writeMemory(MemoryType memType, bitset address, bitset value)
{
  switch (memType)
  {
    case RAM:
      _RAM.write(address, value);
      break;
  }
}

Computer::State Computer::getState() const
{
  return (_state);
}

std::string Computer::dumpRegister(RegisterType regType, Base base) const
{
  auto dump = std::string();
  switch (regType)
  {
    case ProgramCounter:
      dump = bitsetToString(base, _PC.read(), true);
      break;
    case MemoryAdressRegistry:
      dump = bitsetToString(base, _MAR.read(), true);
      break;
    case InstructionRegister:
      dump = bitsetToString(base, _IR.read(), true);
      break;
    case Accumulator:
      dump = bitsetToString(base, _accumulator.read(), true);
      break;
    case Bregister:
      dump = bitsetToString(base, _Breg.read(), true);
      break;
    case Output:
      dump = bitsetToString(base, _output.read(), true);
      break;
    case Status:
      dump = bitsetToString(base, _SR.read(), true);
      break;
  }
  return (dump);
}

size_t Computer::getMemorySize(MemoryType memType) const
{
  switch (memType)
  {
    case RAM:
      return (_RAM.getSize());
      break;
  }
  return (0);
}

size_t Computer::getMemoryUsedSize(MemoryType memType) const
{
  switch (memType)
  {
    case RAM:
      return (_RAM.getUsedSize());
      break;
  }
  return (0);
}

std::vector<std::pair<std::string, std::string>> Computer::dumpMemory(MemoryType memType, Base addrBase, Base valueBase) const
{
  auto dump = std::vector<std::pair<std::string, std::string>>();
  switch (memType)
  {
    case RAM:
      auto rawDump = _RAM.read();
      bitset lastAddress = bitset(App::instance->config.ramAddrBitsize, _RAM.getSize()-1);

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
  return (std::to_string(intFromString(Base::Bin, _output.read().to_string())));
}

std::string Computer::getInstruction() const
{
  const bitset opCode = _IR.read();
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
  auto state = _SR.read();
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
  bitset operand = bitsetRange(_RAM[_MAR.read()].read(), OPCODE_BITSIZE, App::instance->config.ramDataBitsize);
  size_t remainingBits = (App::instance->config.ramAddrBitsize - OPCODE_BITSIZE);
  size_t remainingBlocks = (remainingBits / App::instance->config.ramDataBitsize) + ((remainingBits % App::instance->config.ramDataBitsize) == 0 ? 0 : 1);
  for (size_t currentBlock = 1; currentBlock <= remainingBlocks; currentBlock++)
  {
    //One instruction + operands exceed one memory block, so we need to grab multiple
    operand = bitsetConcat(operand, _RAM[_MAR.read()+currentBlock].read());
  }
  return (operand);
}

void Computer::cycle(int deltaTime)
{
  if (_state != Running) return;
  if (clock.cycle(deltaTime))
  {
    _PC += getInstructionSize(_IR.read());
    _MAR = _PC;
    const bitset opCode = bitsetRange(_RAM[_MAR.read()].read(), 0, OPCODE_BITSIZE);
    _IR.write(opCode); //Read the current instruction and store it in instruction registr
    auto defIt = std::find_if(instructionsSet.begin(), instructionsSet.end(), [&opCode] (InstructionDef def) { return (def.code == opCode); } );
    if (defIt != instructionsSet.end())
    {
      defIt->executor(*this);
    }
  }
}