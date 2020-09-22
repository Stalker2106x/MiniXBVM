#ifndef INSTRUCTION_HH_
#define INSTRUCTION_HH_

#include <unordered_map>
#include <string>
#include <bitset>
#include "Computer/config.h"

const std::unordered_map<std::string, std::bitset<WORD_SIZE>> instructionsSet = {
    {"STR", std::bitset<WORD_SIZE>(0b0000)},
    {"LDA", std::bitset<WORD_SIZE>(0b0001)},
    {"ADD", std::bitset<WORD_SIZE>(0b0010)},
    {"SUB", std::bitset<WORD_SIZE>(0b0011)},
    {"OUT", std::bitset<WORD_SIZE>(0b1110)},
    {"HLT", std::bitset<WORD_SIZE>(0b1111)}
};

template <wordSizeType CodeSize, wordSizeType OperandSize>
class Instruction
{
public:
    Instruction(std::string asmCode)
    {
        try {
            size_t sep = asmCode.find_first_of(" ");
            if (sep == std::string::npos) throw (std::runtime_error("no separator ' ' found"));
            _name = asmCode.substr(0, sep);
            try {
                _code = instructionsSet.at(_name);
            } catch (...) {
                throw (std::runtime_error("instruction "+_name+" is unknown or invalid"));
            }
            for (size_t i = sep + 1; i < asmCode.length(); i += OperandSize)
            {
                std::string operandStr = asmCode.substr(i, i + OperandSize);
                if (operandStr.find_first_not_of("0123456789") != std::string::npos)
                {
                    throw (std::runtime_error("operand should be of numeric type"));
                }
                _operands.push_back(std::bitset<OperandSize>(atoi(operandStr.c_str())));
            }
        } catch (std::runtime_error e) {
            throw (std::runtime_error("Syntax error: "+std::string(e.what())));
        }
    }

    std::string to_string()
    {
        std::string output;

        output = _code.to_string();
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