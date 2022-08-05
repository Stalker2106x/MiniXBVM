#ifndef CC_HH_
#define CC_HH_

#include <string>
#include <sstream>
#include <stdexcept>
#include "Cc/Instruction.hh"

class Cc
{
public:
    std::string compile(std::string buffer, bool &validMachineProgram);
};

#endif /* CC_HH_ */