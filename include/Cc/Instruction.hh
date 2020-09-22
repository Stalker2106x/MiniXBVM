#ifndef INSTRUCTION_HH_
#define INSTRUCTION_HH_

#include <string>
#include <bitset>
#include "Cc/InstructionDef.hh"
#include "Computer/config.h"

const std::unordered_map<std::string, InstructionDef> instructionsSet = {
    {"LDA", InstructionDef("LDA", 0b0000, 1)},
    {"ADD", InstructionDef("ADD", 0b0001, 1)},
    {"SUB", InstructionDef("SUB", 0b0010, 1)},
    {"OUT", InstructionDef("OUT", 0b1110)},
    {"HLT", InstructionDef("HLT", 0b1111)},
};

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
            _name = (sep == std::string::npos ? asmCode : asmCode.substr(0, sep));
            if (instructionsSet.find(_name) == instructionsSet.end())
            {
                throw (std::runtime_error("instruction "+_name+" is unknown or invalid"));
            }
            InstructionDef instructionDefinition = instructionsSet.at(_name);
            _code = instructionDefinition.code;
            if (instructionDefinition.operandCount > 0)
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
                if (_operands.size() < instructionDefinition.operandCount)
                {
                    throw (std::runtime_error("expected "+std::to_string(instructionDefinition.operandCount)+" operands, got " +std::to_string(_operands.size())));
                }
            }
        } catch (std::runtime_error e) {
            throw (std::runtime_error("Syntax error: "+std::string(e.what())));
        }
    }

    std::string to_string()
    {
        std::string output;

        wordSizeType toPad = _operands.size() * OperandSize;
        if (toPad < DWORD_SIZE) output += std::string(toPad, '0');
        output += _code.to_string();
        for (size_t i = 0; i < _operands.size(); i++)
        {
            output += _operands[i].to_string();
        }
        return (output);
    }
private:
    std::string _name;
    std::bitset<CodeSize> _code;
    std::vector<std::bitset<OperandSize>> _operands;
};

#endif /* INSTRUCTION_HH_ */