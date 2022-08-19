#ifndef SEQUENCER_HH_
#define SEQUENCER_HH_

#include <vector>
#include "utils.hh"

class Computer;

struct ControlWordDef
{
public:
    ControlWordDef(std::string mnemonic_, unsigned long long code_, std::function<void(Computer&)> executor_);

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

  static const std::vector<ControlWordDef> controlWords;
};

//Executors
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