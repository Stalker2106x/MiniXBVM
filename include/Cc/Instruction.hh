#ifndef INSTRUCTION_HH_
#define INSTRUCTION_HH_

#include <memory>
#include <string>
#include <bitset>
#include <algorithm>
#include "Cc/InstructionDef.hh"
#include "Computer/config.h"
template <wordSizeType CodeSize, wordSizeType OperandSize>
class Instruction
{
public:
    Instruction(std::string asmCode)
    {
        try {
            if (asmCode.empty()) throw (std::runtime_error("instruction is null"));
            if (asmCode.find_first_not_of("0123456789") == std::string::npos) //only digits, push whole buffer as data
            {
                _operands.push_back(std::bitset<OperandSize>(atoi(asmCode.c_str())));
                return;
            }
            size_t sep = asmCode.find_first_of(" ");
            std::string instructionName = (sep == std::string::npos ? asmCode : asmCode.substr(0, sep));
            auto defIt = std::find_if(instructionsSet.begin(), instructionsSet.end(), [&instructionName] (InstructionDef def) { return (def.name == instructionName); } );
            if (defIt == instructionsSet.end())
            {
                throw (std::runtime_error("instruction "+instructionName+" is unknown or invalid"));
            }
            _definition = std::make_shared<InstructionDef>(*defIt);
            if (_definition->operandCount > 0)
            {
                if (sep == std::string::npos)
                {
                    throw (std::runtime_error("no separator ' ' found"));
                }
                asmCode = asmCode.substr(sep+1, asmCode.length());
                if (!asmCode.empty())
                {
                    if (asmCode.find_first_not_of("0123456789") != std::string::npos)
                    {
                        throw (std::runtime_error("operand should be of numeric type"));
                    }
                    _operands.push_back(std::bitset<OperandSize>(atoi(asmCode.c_str())));
                }
                if (_operands.size() < _definition->operandCount)
                {
                    throw (std::runtime_error("expected "+std::to_string(_definition->operandCount)+" operands, got " +std::to_string(_operands.size())));
                }
            }
        } catch (std::runtime_error e) {
            throw (std::runtime_error("Syntax error: "+std::string(e.what())));
        }
    }

    std::string to_string()
    {
        std::string output;

        if (_definition == nullptr) output += std::string(OperandSize, '0'); //Pad opcode
        else output += _definition->code.to_string();
        for (size_t i = 0; i < _operands.size(); i++)
        {
            output += _operands[i].to_string();
        }
        if (_definition != nullptr && _definition->operandCount == 0) output += std::string(OperandSize, '0'); //Pad value
        return (output);
    }
private:
    std::shared_ptr<InstructionDef> _definition;
    std::vector<std::bitset<OperandSize>> _operands;
};

#endif /* INSTRUCTION_HH_ */