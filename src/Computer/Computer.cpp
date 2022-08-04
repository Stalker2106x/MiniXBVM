#include <algorithm>
#include "Computer/Computer.hh"
#include "Cc/InstructionDef.hh"
#include "bitset_utils.hh"
#include "App.hh"

Computer::Computer()
{
  restart();
}

void Computer::start()
{
  _state = Running;
  App::clock.reset();
}

void Computer::halt()
{
  _state = Off;
  App::clock.setState(Clock::State::Paused);
}

void Computer::restart()
{
  _PC.write(word(_RAM.getSize()-1));
  _MAR.clear();
  _IR.clear();
  _accumulator.clear();
  _Breg.clear();
  _output.clear();
  start();
}

void Computer::reset()
{
  restart();
  _RAM.clear();
}

Computer::State Computer::getState()
{
  return (_state);
}

std::string Computer::dumpRegister(RegisterType regType)
{
  switch (regType)
  {
    case ProgramCounter:
      return (_PC.read().to_string());
      break;
    case MemoryAdressRegistry:
      return (_MAR.read().to_string());
      break;
    case InstructionRegister:
      return (_IR.read().to_string());
      break;
    case Accumulator:
      return (_accumulator.read().to_string());
      break;
    case Bregister:
      return (_Breg.read().to_string());
      break;
    case Output:
      return (_output.read().to_string());
      break;
  }
  return (std::string(""));
}

size_t Computer::getMemorySize(MemoryType memType)
{
  switch (memType)
  {
    case RAM:
      return (_RAM.getSize());
      break;
  }
  return (0);
}

size_t Computer::getMemoryUsedSize(MemoryType memType)
{
  switch (memType)
  {
    case RAM:
      return (_RAM.getUsedSize());
      break;
  }
  return (0);
}

std::vector<std::pair<std::string, std::string>> Computer::dumpMemory(MemoryType memType)
{
  switch (memType)
  {
    case RAM:
      return (_RAM.dump());
      break;
  }
  return (std::vector<std::pair<std::string, std::string>>());
}

std::string Computer::getOutput()
{
  return (std::to_string(_output.read().to_ulong()));
}

std::string Computer::getInstruction()
{
  word opCode = bitsetRange<DWORD_SIZE, WORD_SIZE>(_IR.read(), WORD_SIZE, DWORD_SIZE);
  auto defIt = std::find_if(instructionsSet.begin(), instructionsSet.end(), [&opCode] (InstructionDef def) { return (def.code == opCode); } );
  if (defIt != instructionsSet.end())
  {
    return (defIt->name);
  }
  return ("XXX");
}

void Computer::cycle()
{
  if (_state != Running) return;
  ++_PC;
  _MAR = _PC;
  _IR.write(_RAM[_MAR.read()].read()); //Rea)d the current instruction and store it in instruction registr
  word opCode = bitsetRange<DWORD_SIZE, WORD_SIZE>(_IR.read(), WORD_SIZE, DWORD_SIZE);
  auto defIt = std::find_if(instructionsSet.begin(), instructionsSet.end(), [&opCode] (InstructionDef def) { return (def.code == opCode); } );
  if (defIt != instructionsSet.end())
  {
    defIt->executor(*this);
  }
}