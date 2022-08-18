#ifndef COMPUTER_HH_
#define COMPUTER_HH_

#include <map>
#include <unordered_map>
#include "Computer/Memory.hh"
#include "Computer/Register.hh"
#include "config.h"
#include "Clock.hh"
#include "utils.hh"

class Schematic;

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

  std::string dumpRegister(const std::string &regType, Base base) const;
  Memory &getMemory(const std::string &memType);
  Register &getRegister(const std::string &regType);
  const Memory &getMemory(const std::string &memType) const;
  const Register &getRegister(const std::string &regType) const;
  std::vector<std::pair<std::string, std::string>> dumpMemory(const std::string &memType, Base addrBase, Base valueBase) const;
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

  friend Schematic;

  Clock clock;
private:
  State _state;
  std::unordered_map<std::string, Memory> _memories;
  std::unordered_map<std::string, Register> _registers;
};

#endif /* !COMPUTER_HH_ */