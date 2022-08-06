#include <algorithm>
#include "Computer/Computer.hh"
#include "Cc/InstructionDef.hh"
#include "bitset_utils.hh"
#include "App.hh"

Computer::Computer(int addrSize, int regSize)
  : _RAM(addrSize, regSize), _PC(regSize), _MAR(regSize), _IR(regSize),
    _accumulator(regSize), _Breg(regSize), _SR(regSize), _output(regSize)
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
  _PC.write(bitset(WORD_SIZE, _RAM.getSize()-1));
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
      bitset lastAddress = bitset(ADDRESS_SIZE, _RAM.getSize()-1);

      for (bitset it = bitset(ADDRESS_SIZE, 0); it < lastAddress; ++it)
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
  bitset opCode = bitsetRange(_IR.read(), WORD_SIZE, DWORD_SIZE);
  auto defIt = std::find_if(instructionsSet.begin(), instructionsSet.end(), [&opCode] (InstructionDef def) { return (def.code == opCode); } );
  if (defIt != instructionsSet.end())
  {
    return (defIt->name);
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

void Computer::cycle(int deltaTime)
{
  if (_state != Running) return;
  if (clock.cycle(deltaTime))
  {
    ++_PC;
    _MAR = _PC;
    _IR.write(_RAM[_MAR.read()].read()); //Read the current instruction and store it in instruction registr
    bitset opCode = bitsetRange(_IR.read(), WORD_SIZE, DWORD_SIZE);
    auto defIt = std::find_if(instructionsSet.begin(), instructionsSet.end(), [&opCode] (InstructionDef def) { return (def.code == opCode); } );
    if (defIt != instructionsSet.end())
    {
      defIt->executor(*this);
    }
  }
}