#ifndef CC_HH_
#define CC_HH_

#include <string>

class Cc
{
public:
    std::string compile(std::string buffer, bool &validMachineProgram);
    std::string parseData(const std::string &buffer);
};

#endif /* CC_HH_ */