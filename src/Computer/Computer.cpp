#include <algorithm>
#include "Computer/Computer.hh"
#include "Cc/InstructionDef.hh"
#include "bitset_utils.hh"
#include "App.hh"
#include "utils.hh"

Computer::Computer()
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
  _PC.write(word(_RAM.getSize()-1));
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

Computer::State Computer::getState() const
{
  return (_state);
}

std::string Computer::dumpRegister(RegisterType regType, bool format) const
{
  auto dump = std::string();
  switch (regType)
  {
    case ProgramCounter:
      dump = _PC.read().to_string();
      break;
    case MemoryAdressRegistry:
      dump = _MAR.read().to_string();
      break;
    case InstructionRegister:
      dump = _IR.read().to_string();
      break;
    case Accumulator:
      dump = _accumulator.read().to_string();
      break;
    case Bregister:
      dump = _Breg.read().to_string();
      break;
    case Output:
      dump = _output.read().to_string();
      break;
    case Status:
      dump = _SR.read().to_string();
      break;
  }
  if (format) dump = formatBinaryString(dump);
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

std::vector<std::pair<std::string, std::string>> Computer::dumpMemory(MemoryType memType, bool format) const
{
  auto dump = std::vector<std::pair<std::string, std::string>>();
  switch (memType)
  {
    case RAM:
      dump = _RAM.dump();
      break;
  }
  if (format)
  {
    for (size_t i = 0; i < dump.size(); i++)
    {
      dump[i].second = formatBinaryString(dump[i].second);
    }
  }
  return (dump);
}

std::string Computer::getOutput() const
{
  return (std::to_string(_output.read().to_ulong()));
}

std::string Computer::getInstruction() const
{
  word opCode = bitsetRange<DWORD_SIZE, WORD_SIZE>(_IR.read(), WORD_SIZE, DWORD_SIZE);
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
    word opCode = bitsetRange<DWORD_SIZE, WORD_SIZE>(_IR.read(), WORD_SIZE, DWORD_SIZE);
    auto defIt = std::find_if(instructionsSet.begin(), instructionsSet.end(), [&opCode] (InstructionDef def) { return (def.code == opCode); } );
    if (defIt != instructionsSet.end())
    {
      defIt->executor(*this);
    }
  }
}