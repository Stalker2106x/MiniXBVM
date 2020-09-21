#ifndef COMPUTER_HH_
#define COMPUTER_HH_

#include <unordered_map>
#include "Computer/Display.hh"
#include "Computer/Input.hh"
#include "Computer/Memory.hh"
#include "Computer/Register.hh"
#include "Computer/ControllerSequencer.hh"
#include "Computer/Arithmetic.hh"
#include "Computer/config.h"

enum RegisterType {
  ProgramCounter,
  MemoryAdressRegistry,
  InstructionRegister,
  Accumulator,
  Bregister,
  Output
};

enum MemoryType {
  RAM
};

class Computer
{
public:
  Computer();

  std::string dumpRegister(RegisterType regType);
  size_t getMemorySize(MemoryType memType);
  std::vector<std::pair<std::string, std::string>> dumpMemory(MemoryType memType);

  void cycle();
  void execute();

private:
  std::unordered_map<std::string, std::bitset<WORD_SIZE>> _instructionSet;

  ControllerSequencer _controllerSequencer;
  Input _input;
  Display _display;

  Memory<WORD_SIZE, DWORD_SIZE> _RAM;

  Register<WORD_SIZE> _PC;
  Register<WORD_SIZE> _MAR;
  Register<DWORD_SIZE> _IR;
  Register<DWORD_SIZE> _accumulator;
  Register<DWORD_SIZE> _Breg;
  Register<DWORD_SIZE> _output;
};

#endif /* !COMPUTER_HH_ */