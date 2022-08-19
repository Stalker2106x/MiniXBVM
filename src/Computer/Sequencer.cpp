#include "Computer/Sequencer.hh"
#include "Computer/Computer.hh"
#include "App.hh"


ControlWordDef::ControlWordDef(std::string mnemonic_, unsigned long long code_, std::function<void(Computer&)> executor_)
: mnemonic(mnemonic_), code(OPCODE_BITSIZE, code_), executor(executor_)
{
}

const std::vector<ControlWordDef> Sequencer::controlWords = {
  {"HLT", 1, Control::HLTExecutor},
  {"MI", 2, Control::MIExecutor},
  {"RO", 3, Control::ROExecutor},
  {"RI", 4, Control::RIExecutor},
  {"IO", 5, Control::IOExecutor},
  {"II", 6, Control::IIExecutor},
  {"AO", 7, Control::AOExecutor},
  {"AI", 8, Control::AIExecutor},
  {"EO", 9, Control::EOExecutor},
  {"SU", 10, Control::SUExecutor},
  {"BI", 11, Control::BIExecutor},
  {"OI", 12, Control::OIExecutor},
  {"CE", 13, Control::CEExecutor},
  {"CO", 14, Control::COExecutor},
  {"JP", 15, Control::JPExecutor},
  {"FI", 16, Control::FIExecutor}
};

Sequencer::Sequencer()
{
}

void Sequencer::drive(const std::string &mnemonic)
{
  auto line = std::find_if(controlWords.begin(), controlWords.end(), [&mnemonic] (ControlWordDef def) { return (def.mnemonic == mnemonic); } );
  line->executor(*App::instance->computer);
}

void Sequencer::fetch()
{
  drive("CO");
  drive("MI");
  
  drive("RO");
  drive("II");
  drive("CE");
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
  }

  void SUExecutor(Computer &computer)
  {

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

  }

}