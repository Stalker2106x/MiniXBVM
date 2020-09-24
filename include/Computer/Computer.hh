#ifndef COMPUTER_HH_
#define COMPUTER_HH_

#include <unordered_map>
#include "Computer/Memory.hh"
#include "Computer/Register.hh"
#include "config.h"

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
  enum State {
    Off,
    Running
  };

  Computer();

  void start();
  void halt();
  void restart();
  void reset();
  State getState();

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

  std::string dumpRegister(RegisterType regType);
  size_t getMemorySize(MemoryType memType);
  std::vector<std::pair<std::string, std::string>> dumpMemory(MemoryType memType);
  std::string getOutput();
  std::string getInstruction();

  void cycle();

  //EXECUTORS
  friend void LDAExecutor(Computer &computer);
  friend void ADDExecutor(Computer &computer);
  friend void SUBExecutor(Computer &computer);
  friend void MULExecutor(Computer &computer);
  friend void OUTExecutor(Computer &computer);
  friend void HLTExecutor(Computer &computer);

private:
  State _state;
  Memory<WORD_SIZE, DWORD_SIZE> _RAM;

  Register<WORD_SIZE> _PC;
  Register<WORD_SIZE> _MAR;
  Register<DWORD_SIZE> _IR;
  Register<DWORD_SIZE> _accumulator;
  Register<DWORD_SIZE> _Breg;
  Register<DWORD_SIZE> _output;
};

#endif /* !COMPUTER_HH_ */