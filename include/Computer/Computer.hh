#ifndef COMPUTER_HH_
#define COMPUTER_HH_

#include <map>
#include <unordered_map>
#include "Computer/Memory.hh"
#include "Computer/Register.hh"
#include "config.h"
#include "Clock.hh"
#include "utils.hh"

enum RegisterType {
  ProgramCounter,
  MemoryAdressRegistry,
  InstructionRegister,
  Accumulator,
  BRegister,
  Output,
  StatusRegister
};

enum MemoryType {
  RAM
};

class Computer
{
public:
  enum State {
    Off,
    Running
  };

  Computer();

  void start();
  void halt();
  void restart();
  void reset();
  State getState() const;

  std::string dumpRegister(RegisterType regType, Base base) const;
  Memory &getMemory(MemoryType memType);
  Register &getRegister(RegisterType regType);
  const Memory &getMemory(MemoryType memType) const;
  const Register &getRegister(RegisterType regType) const;
  std::vector<std::pair<std::string, std::string>> dumpMemory(MemoryType memType, Base addrBase, Base valueBase) const;
  std::string getOutput() const;
  std::string getInstruction() const;
  std::string getFlags() const;

  bitset getOperandBitset() const;
  size_t getPCIncrement() const;

  void cycle(int deltaTime);

  //EXECUTORS
  friend void LDAExecutor(Computer &computer);
  friend void ADDExecutor(Computer &computer);
  friend void SUBExecutor(Computer &computer);
  friend void MULExecutor(Computer &computer);
  friend void OUTExecutor(Computer &computer);
  friend void HLTExecutor(Computer &computer);

  Clock clock;
private:
  State _state;
  std::unordered_map<MemoryType, Memory> _memories;
  std::unordered_map<RegisterType, Register> _registers;
};

#endif /* !COMPUTER_HH_ */