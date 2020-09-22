#include <iostream>
#include <algorithm>
#include "Computer/Computer.hh"
#include "Cc/InstructionDef.hh"

Computer::Computer()
{
  _PC.write(word(0b0000));
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
  unsigned long outputValue = _output.read().to_ulong();
  int digits = 0;
  if (outputValue < 0) digits = 1; // remove this line if '-' counts as a digit
  while (outputValue) {
      outputValue /= 10;
      digits++;
  }
  return (std::string(5-digits, '0')+std::to_string(_output.read().to_ulong()));
}

void Computer::cycle()
{
  _MAR = _PC;
  ++_PC;
  _IR.write(_RAM[_MAR.read()].read()); //Rea)d the current instruction and store it in instruction registr

  execute();
}

void Computer::execute()
{
  word opCode = Arithmetic::range<DWORD_SIZE, WORD_SIZE>(_IR.read(), 0, WORD_SIZE-1);
  auto defIt = std::find_if(instructionsSet.begin(), instructionsSet.end(), [&opCode] (InstructionDef def) { return (def.code == opCode); } );
  if (defIt != instructionsSet.end())
  {
    defIt->executor(*this);
  }
}