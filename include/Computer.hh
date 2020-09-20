#ifndef COMPUTER_HH_
#define COMPUTER_HH_

#include <unordered_map>
#include "Display.hh"
#include "Input.hh"
#include "Register.hh"
#include "ControllerSequencer.hh"
#include "Arithmetic.hh"
#include "config.h"

class Computer
{
public:
  Computer();
  void cycle();
  void execute();

private:
  std::unordered_map<std::string, std::bitset<WORD_SIZE>> _instructionSet;

  ControllerSequencer _controllerSequencer;
  Input _input;
  Display _display;

  Register<1,        WORD_SIZE> _PC;
  Register<1,        WORD_SIZE> _MAR;
  Register<RAM_SIZE, DWORD_SIZE> _RAM;
  Register<1,        DWORD_SIZE> _IR;

  Register<1,        DWORD_SIZE> _accumulator;
  Register<1,        DWORD_SIZE> _Breg;
  Register<1,        DWORD_SIZE> _output;
};

#endif /* !COMPUTER_HH_ */