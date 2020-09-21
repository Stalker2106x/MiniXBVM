#ifndef CC_HH_
#define CC_HH_

#include "config.h"

template<wordSizeType WordSize>
class Cc
{
public:
    std::vector<std::bitset<WordSize>> Cc::compile(std::string fullBuffer)
    {
        std::stringstream ss(fullBuffer);
        std::vector<std::bitset<WordSize>> output;
        std::string buffer;

        while(std::getline(ss, buffer, '\n'))
        {
            size_t sep = buffer.find_first_of(" ");
            std::string op = buffer.substr(0, sep);
            std::string val = buffer.substr(sep + 1, buffer.length);
            //treat
        }
        return (output);
    }


};

#endif /* CC_HH_ */