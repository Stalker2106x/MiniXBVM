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
    template <wordSizeType WordSize>
    static std::string compile(std::string buffer, bool &validMachineProgram)
    {
        int lineNumber = 1;
        std::istringstream ss(buffer);
        std::string errOutput;
        std::string output;
        std::string asmCode;

        while(std::getline(ss, asmCode, '\n'))
        {
            try {
                if (asmCode.empty()) continue;
                size_t sep = asmCode.find_first_of(" ");
                if (sep == std::string::npos) //no separator, check if is data
                {
                    try {
                        output += binStringFromInt128<WordSize*2>(int128FromString(asmCode)) + '\n';
                        continue; //We consider it processed
                    } catch (...) {
                        //It was not data, continue gracefully...
                    }
                }
                std::string instructionName = (sep == std::string::npos ? asmCode : asmCode.substr(0, sep));
                auto defIt = std::find_if(instructionsSet.begin(), instructionsSet.end(), [&instructionName] (InstructionDef def) { return (def.name == instructionName); } );
                if (defIt == instructionsSet.end())
                {
                    throw (std::runtime_error("instruction "+instructionName+" is unknown or invalid"));
                }
                Instruction<WordSize, WordSize> instr(*defIt, asmCode, sep);

                output += instr.to_string()+"\n";
            } catch (std::runtime_error e) {
                errOutput += "Line "+std::to_string(lineNumber)+":"+e.what()+"\n";
            }
            lineNumber++;
        }
        if (!errOutput.empty() || !output.size())
        {
            validMachineProgram = false;
            return (errOutput);
        }
        else
        {
            validMachineProgram = true;
            return (output);
        }
    }
};

#endif /* CC_HH_ */