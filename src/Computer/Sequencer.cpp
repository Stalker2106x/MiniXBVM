#include "Computer/Sequencer.hh"
#include "Computer/Computer.hh"
#include "App.hh"
#include "Cc/InstructionDef.hh"
#include <iostream>


ControlWordDef::ControlWordDef(std::string mnemonic_, size_t code_, std::function<void(Computer&)> executor_)
: mnemonic(mnemonic_), code(OPCODE_BITSIZE, code_), executor(executor_)
{
}

const std::vector<InstructionDef> InstructionDef::set = {
  {"NOP", 0, Sequencer::NOPExecutor},
  {"LDA", 1, Sequencer::LDAExecutor, 1},
  {"ADD", 2, Sequencer::ADDExecutor, 1},
  {"SUB", 3, Sequencer::SUBExecutor, 1},
  {"OUT", 5, Sequencer::OUTExecutor},
  {"HLT", 6, Sequencer::HLTExecutor}
};

namespace Sequencer {

  void drive(const std::string &mnemonic)
  {
    auto line = std::find_if(controlWords.begin(), controlWords.end(), [&mnemonic] (ControlWordDef def) { return (def.mnemonic == mnemonic); } );
    line->executor(*App::instance->computer);
  }

  void fetch()
  {
    drive("CO");
    drive("MI");
    
    drive("RO");
    drive("II");
    drive("CE");
  }

  void execute(Computer &computer)
  {
    bitset opCode = bitsetRange(computer.getRegister("InstructionRegister").read(), 0, OPCODE_BITSIZE);
    std::cout << opCode.to_string();
    auto instr = std::find_if(InstructionDef::set.begin(), InstructionDef::set.end(), [&opCode] (InstructionDef def) { return (def.opCode == opCode); } );
    if (instr == InstructionDef::set.end()) throw std::runtime_error("Unknown instruction");
    instr->executor(computer);
  }


  void NOPExecutor(Computer &computer)
  {
      return; //Do nothing
  }

  void LDAExecutor(Computer &computer)
  {
    drive("IO");
    drive("MI");
    drive("RO");
    drive("AI");
  }

  void ADDExecutor(Computer &computer)
  {
    drive("IO");
    drive("MI");
    drive("RO");
    drive("BI");
    drive("EO");
    drive("AI");
  }

  void SUBExecutor(Computer &computer)
  {
    drive("IO");
    drive("MI");
    drive("RO");
    drive("BI");
    drive("SU");
    drive("AI");
  }

  void OUTExecutor(Computer &computer)
  {
    drive("AO");
    drive("OI");
  }

  void HLTExecutor(Computer &computer)
  {
    computer.halt();
  }
}

namespace Control {

  void HLTExecutor(Computer &computer)
  {
    computer.clock.setState(Clock::State::Paused);
  }

  void MIExecutor(Computer &computer)
  {
    computer.getRegister("MemoryAdressRegister").write(computer.bus);
  }

  void ROExecutor(Computer &computer)
  {
    computer.bus = computer.getMemory("RAM").read(computer.getRegister("MemoryAdressRegister").read());
  }

  void RIExecutor(Computer &computer)
  {
    computer.getMemory("RAM").write(computer.getRegister("MemoryAdressRegister").read(), computer.bus);
  }

  void IOExecutor(Computer &computer)
  {
    computer.bus = bitsetRange(computer.getRegister("InstructionRegister").read(), OPCODE_BITSIZE, App::instance->config.ramDataBitsize);
  }

  void IIExecutor(Computer &computer)
  {
    computer.getRegister("InstructionRegister").write(computer.bus);
  }

  void AOExecutor(Computer &computer)
  {
    computer.bus = computer.getRegister("Accumulator").read();
  }

  void AIExecutor(Computer &computer)
  {
    computer.getRegister("Accumulator").write(computer.bus);
  }

  void EOExecutor(Computer &computer)
  {
    computer.bus = computer.getRegister("Accumulator").read() + computer.getRegister("BRegister").read();
  }

  void SUExecutor(Computer &computer)
  {
    computer.bus = computer.getRegister("Accumulator").read() - computer.getRegister("BRegister").read();
  }

  void BIExecutor(Computer &computer)
  {
    computer.getRegister("BRegister").write(computer.bus);
  }

  void OIExecutor(Computer &computer)
  {
    computer.getRegister("Output").write(computer.bus);
  }

  void CEExecutor(Computer &computer)
  {
    Register &pc = computer.getRegister("ProgramCounter");
    pc.write(pc.read() += 1);
  }

  void COExecutor(Computer &computer)
  {
    computer.bus = computer.getRegister("ProgramCounter").read();
  }

  void JPExecutor(Computer &computer)
  {
    computer.getRegister("ProgramCounter").write(computer.bus);
  }

  void FIExecutor(Computer &computer)
  {
    return; //?? Latch the current state of the flags (ZF and CF) into the flags register (FR) 
  }

}