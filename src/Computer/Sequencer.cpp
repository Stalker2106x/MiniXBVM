#include "Computer/Sequencer.hh"
#include "Computer/Computer.hh"
#include "App.hh"
#include "Cc/InstructionDef.hh"


ControlWordDef::ControlWordDef(std::string mnemonic_, size_t code_, std::function<void(Computer&)> executor_)
: mnemonic(mnemonic_), code(OPCODE_BITSIZE, code_), executor(executor_)
{
}

const std::vector<InstructionDef> InstructionDef::set = {
  {"NOP", 0, &Sequencer::NOPExecutor},
  {"LDA", 1, &Sequencer::LDAExecutor, 1},
  {"ADD", 2, &Sequencer::ADDExecutor, 1},
  {"SUB", 3, &Sequencer::SUBExecutor, 1},
  {"MUL", 4, &Sequencer::MULExecutor, 1},
  {"OUT", 5, &Sequencer::OUTExecutor},
  {"HLT", 6, &Sequencer::HLTExecutor}
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
    bitset opCode = computer.getRegister("InstructionRegister").read();
    auto instr = std::find_if(InstructionDef::set.begin(), InstructionDef::set.end(), [&opCode] (InstructionDef def) { return (def.opCode == opCode); } );
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
    drive("AI");
  }

  void SUBExecutor(Computer &computer)
  {
    Memory &ram = computer.getMemory("RAM");
    computer.getRegister("MemoryAdressRegister").write(bitsetRange(computer.getOperandBitset(), 0, App::instance->config.ramAddrBitsize)); //Extract adress from Current RAM Block
    computer.getRegister("BRegister").write(ram[computer.getRegister("MemoryAdressRegister").read()].read());
    computer.getRegister("Accumulator") -= computer.getRegister("BRegister");
  }

  void MULExecutor(Computer &computer)
  {
    Memory &ram = computer.getMemory("RAM");
    computer.getRegister("MemoryAdressRegister").write(bitsetRange(computer.getOperandBitset(), 0, App::instance->config.ramAddrBitsize)); //Extract adress from Current RAM Block
    computer.getRegister("BRegister").write(ram[computer.getRegister("MemoryAdressRegister").read()].read());
    computer.getRegister("Accumulator") *= computer.getRegister("BRegister");
  }

  void OUTExecutor(Computer &computer)
  {
    computer.getRegister("Output").write(computer.getRegister("Accumulator").read()); //Extract acc to output
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
    computer.bus = computer.getRegister("InstructionRegister").read();
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