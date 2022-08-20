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

class Sequencer
{
public:
  Sequencer();

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

  static const std::vector<ControlWordDef> controlWords;
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

#endif /* !SEQUENCER_HH_ */