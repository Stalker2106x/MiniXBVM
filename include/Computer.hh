#ifndef COMPUTER_HH_
#define COMPUTER_HH_

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

private:
  ControllerSequencer _controllerSequencer;
  Arithmetic _arithmetic;
  Input _input;

  Register<1, WORD_SIZE> _programCounter;
  Register<1, WORD_SIZE> _mar;
  Register<RAM_SIZE, DWORD_SIZE> _ram;
  Register<1, WORD_SIZE> _instructions;
  Register<1, WORD_SIZE> _accumulator;
  Register<1, WORD_SIZE> _b;
  Register<1, WORD_SIZE> _output;
};

#endif /* !COMPUTER_HH_ */