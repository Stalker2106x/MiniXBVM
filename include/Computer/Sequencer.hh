#ifndef SEQUENCER_HH_
#define SEQUENCER_HH_

#include <vector>
#include "utils.hh"

class Computer;

struct ControlWordDef
{
public:
    ControlWordDef(std::string mnemonic_, size_t code_, std::function<void(Computer&)> executor_);

    std::string mnemonic;
    bitset code;
    std::function<void(Computer&)> executor;
};

//Control Executors
namespace Control {
  void HLTExecutor(Computer &computer);
  void MIExecutor(Computer &computer);
  void ROExecutor(Computer &computer);
  void RIExecutor(Computer &computer);
  void IOExecutor(Computer &computer);
  void IIExecutor(Computer &computer);
  void AOExecutor(Computer &computer);
  void AIExecutor(Computer &computer);
  void EOExecutor(Computer &computer);
  void SUExecutor(Computer &computer);
  void BIExecutor(Computer &computer);
  void OIExecutor(Computer &computer);
  void CEExecutor(Computer &computer);
  void COExecutor(Computer &computer);
  void JPExecutor(Computer &computer);
  void FIExecutor(Computer &computer);
}

namespace Sequencer
{
  void drive(const std::string &mnemonic);

  void fetch();
  void execute(Computer &computer);

  //Executors
  void NOPExecutor(Computer &computer);
  void LDAExecutor(Computer &computer);
  void ADDExecutor(Computer &computer);
  void SUBExecutor(Computer &computer);
  void MULExecutor(Computer &computer);
  void OUTExecutor(Computer &computer);
  void HLTExecutor(Computer &computer);

  static const std::vector<ControlWordDef> controlWords = {
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
}

#endif /* !SEQUENCER_HH_ */