#ifndef CC_HH_
#define CC_HH_

#include <string>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include "Computer/config.h"

const std::unordered_map<std::string, std::bitset<WORD_SIZE>> instructionsSet = {
    {"LDA", std::bitset<WORD_SIZE>(0b0000)},
    {"ADD", std::bitset<WORD_SIZE>(0b0001)},
    {"SUB", std::bitset<WORD_SIZE>(0b0010)},
    {"OUT", std::bitset<WORD_SIZE>(0b1110)},
    {"HLT", std::bitset<WORD_SIZE>(0b1111)}
};

class Cc
{
public:
    template<wordSizeType WordSize>
    static std::string compile(std::string fullBuffer)
    {
        int lineNumber = 0;
        std::istringstream ss(fullBuffer);
        std::string output;
        std::string buffer;

        while(std::getline(ss, buffer, '\n'))
        {
            try {
                size_t sep = buffer.find_first_of(" ");
                if (sep == std::string::npos) return ("Syntax error on line "+lineNumber);
                output += instructionsSet.at(buffer.substr(0, sep)).to_string() + " " + buffer.substr(sep + 1, buffer.length());
                ++lineNumber;
            } catch (...) {
                return ("Syntax error on line "+lineNumber);
            }
        }
        return (output);
    }
};

#endif /* CC_HH_ */