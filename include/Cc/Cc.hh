#ifndef CC_HH_
#define CC_HH_

#include <string>
#include <map>
#include <cctype>

struct invalid_varname {
    bool operator()(char c) {
        return (!std::isalpha(c) && !std::isdigit(c));
    }
};

class Cc
{
public:
    struct Output {
        Output() : success(true) {};

        bool success;
        std::string code;
        std::string log;
    };

    Output compile(const std::string &input);

private:
    struct Variable {
        std::string name;
        std::string address;
        std::string value;
        size_t bits;
    };
    typedef std::map<std::string, Variable> Heap;

    std::string parseValue(const std::string &buffer);
    std::string parseOperand(const std::string &buffer);
    Variable parseVariable(const std::string &line, const size_t lineNumber);
    void eraseLine(std::string &data, const std::string &line);
    
    void dumpHeap(std::string &outputCode);

    Heap heap;
};

#endif /* CC_HH_ */