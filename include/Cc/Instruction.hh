#ifndef INSTRUCTION_HH_
#define INSTRUCTION_HH_

#include <string>
#include <bitset>
#include <algorithm>
#include "Cc/InstructionDef.hh"
#include "Computer/config.h"
#include "bitset_utils.hh"

template <wordSizeType CodeSize, wordSizeType OperandSize>
class Instruction
{
public:

    Instruction(InstructionDef definition, std::string asmCode, size_t sep)
    : _definition(definition)
    {
        try {
            if (_definition.operandCount > 0)
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
                    _operands.push_back(bitsetFromString<OperandSize>(binaryStringFromString<OperandSize>(asmCode)));
                }
                if (_operands.size() < _definition.operandCount)
                {
                    throw (std::runtime_error("expected "+std::to_string(_definition.operandCount)+" operands, got " +std::to_string(_operands.size())));
                }
            }
        } catch (std::runtime_error e) {
            throw (std::runtime_error("Syntax error: "+std::string(e.what())));
        }
    }

    std::string to_string()
    {
        std::string output;

        output += _definition.code.to_string();
        for (size_t i = 0; i < _operands.size(); i++)
        {
            output += _operands[i].to_string();
        }
        if (_definition.operandCount == 0) output += std::string(OperandSize, '0'); //Pad value
        return (output);
    }
private:
    InstructionDef _definition;
    std::vector<std::bitset<OperandSize>> _operands;
};

#endif /* INSTRUCTION_HH_ */