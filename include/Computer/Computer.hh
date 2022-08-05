#ifndef COMPUTER_HH_
#define COMPUTER_HH_

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
  Bregister,
  Output,
  Status
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

  template<wordSizeType AddrSize, wordSizeType RegSize>
  void writeMemory(MemoryType memType, std::bitset<AddrSize> address, std::bitset<RegSize> value)
  {
    switch (memType)
    {
      case RAM:
        _RAM.write(address, value);
        break;
    }
  }

  std::string dumpRegister(RegisterType regType, Base base) const;
  size_t getMemorySize(MemoryType memType) const;
  size_t getMemoryUsedSize(MemoryType memType) const;
  std::vector<std::pair<std::string, std::string>> dumpMemory(MemoryType memType, Base addrBase, Base valueBase) const;
  std::string getOutput() const;
  std::string getInstruction() const;
  std::string getFlags() const;

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
  Memory<ADDRESS_SIZE, DWORD_SIZE> _RAM;

  Register<WORD_SIZE> _PC;
  Register<WORD_SIZE> _MAR;
  Register<DWORD_SIZE> _IR;
  Register<DWORD_SIZE> _accumulator;
  Register<DWORD_SIZE> _Breg;
  Register<WORD_SIZE> _SR;
  Register<DWORD_SIZE> _output;
};

#endif /* !COMPUTER_HH_ */