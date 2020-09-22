#ifndef CC_HH_
#define CC_HH_

#include <string>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include "Cc/Instruction.hh"

class Cc
{
public:
    template<wordSizeType WordSize>
    static std::string compile(std::string fullBuffer)
    {
        int lineNumber = 1;
        std::istringstream ss(fullBuffer);
        std::string errOutput;
        std::string output;
        std::string buffer;

        while(std::getline(ss, buffer, '\n'))
        {
            try {
                Instruction<WORD_SIZE, WORD_SIZE> instr(buffer);

                output += instr.to_string()+"\n";
            } catch (std::runtime_error e) {
                errOutput += "Line "+std::to_string(lineNumber)+":"+e.what()+"\n";
            }
            lineNumber++;
        }
        return (errOutput.empty() ? output : errOutput);
    }
};

#endif /* CC_HH_ */