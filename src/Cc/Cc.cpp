#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <variant>
#include "Cc/Cc.hh"
#include "Cc/InstructionDef.hh"
#include "utils.hh"

Cc::Output Cc::compile(const std::string &input)
{
    std::string inputProcessed(input);
    Output output;
    std::string line;

    //Pass 0: Declarative: We gather variable and labels definition into heap
    //Pass 1: Implementation: We generate the code
    for (size_t pass = 0; pass <= 1; pass++)
    {
        int lineNumber = 0;
        std::istringstream iss(inputProcessed);
        while(std::getline(iss, line, '\n'))
        {
            try {
                if (line.empty()) continue; //Skip empty line
                std::istringstream lss(line);
                std::string buffer;

                lineNumber++;
                //Parse first word (usually instruction)
                lss >> buffer;
                std::string keyword(buffer);
                std::transform(keyword.begin(), keyword.end(), keyword.begin(), ::toupper);
                auto instructionsIt = std::find_if(instructionsSet.begin(), instructionsSet.end(), [&keyword] (InstructionDef def) { return (def.keyword == keyword); } );
                if (instructionsIt == instructionsSet.end())
                {
                    if (pass == 0) //Instruction was not found, pass 0, we consider that it is a variable
                    {
                        Variable var = parseVariable(line, lineNumber);
                        heap.emplace(var.name, var);
                        eraseLine(inputProcessed, line); //No need to parse it later
                        continue;
                    }
                    else if (pass == 1)
                    {
                        //its probably garbage...
                        throw (std::runtime_error("instruction "+buffer+" is unknown or invalid"));
                    }
                }
                else
                {
                    if (pass == 1)
                    {
                        output.code += instructionsIt->code.to_string();
                        //Pad with zeros if no operands are expected
                        if (instructionsIt->operandCount == 0) output.code += "0000";
                    }
                }
                if (pass == 0) continue; //We skip operand parsing on declarative pass
                //Parse remaining line if any
                int operandsFound = 0;
                while (lss >> buffer)
                {
                    output.code += parseOperand(buffer);
                    operandsFound += 1;
                }
                if (instructionsIt->operandCount != operandsFound)
                {
                    throw (std::runtime_error("instruction "+instructionsIt->keyword+" expects "+std::to_string(instructionsIt->operandCount)+" operands, "+std::to_string(operandsFound)+" found."));
                }
                output.code += '\n';
            } catch (std::runtime_error e) {
                output.log += "Line "+std::to_string(lineNumber)+":"+e.what()+"\n";
                output.success = false; //Invalidate machine program immediately
            }
        }
    }
    if (output.success) output.log += "Compiled with success!\n";
    else output.log += "Compilation aborted due to unrecoverable errors\n";
    dumpHeap(output.code);
    return (output);
}

Cc::Variable Cc::parseVariable(const std::string &line, const size_t lineNumber)
{
    std::istringstream lss(line);
    std::string buffer;
    Cc::Variable var;

    if (lss >> buffer) //Parse name
    {
        if (std::isdigit(buffer[0]) || std::find_if(buffer.begin(), buffer.end(), not_alphanumeric()) != buffer.end())
        {
            throw (std::runtime_error("failed to parse variable "+buffer+": invalid name (Only letters and digits, cannot start with a digit)"));
        }
        var.name = buffer;
        if (lss >> buffer) //Parse size
        {
            if (buffer == "db") var.bits = BYTE_SIZE;
            else if (buffer == "dw") var.bits = WORD_SIZE;
            else if (buffer == "dd") var.bits = DWORD_SIZE;
            else throw (std::runtime_error("failed to parse variable "+var.name+": Size "+buffer+" unknown, can be any of: db, dw, dd"));
            if (lss >> buffer) //Parse value
            {
                var.value = bitsetToString(Base::Bin, bitset(DWORD_SIZE, intFromString(Base::Unknown, buffer)));
            }
            else
            {
                throw (std::runtime_error("failed to parse variable "+var.name+": No value given"));
            }
        }
        else
        {
            throw (std::runtime_error("failed to parse variable "+var.name+": No size given"));
        }
    }
    else
    {
        throw (std::runtime_error("failed to parse variable"));
    }
    //Since we have a valid var, we can assign its address before leaving (address = lineNumber-1)
    var.address = bitsetToString(Base::Bin, bitset(WORD_SIZE, lineNumber-1));
    return (var);
}

std::string Cc::parseValue(const std::string &buffer)
{
    try {
        return (bitsetToString(Base::Bin, bitset(WORD_SIZE, intFromString(Base::Unknown, buffer))));
    } catch (...) {
        throw (std::runtime_error("failed to parse operand "+buffer+": invalid integer"));
    }
}

std::string Cc::parseOperand(const std::string &buffer)
{
    if (!std::isdigit(buffer[0]) && std::find_if(buffer.begin(), buffer.end(), not_alphanumeric()) == buffer.end()) //Looks like a variable
    {
        if (heap.find(buffer) != heap.end())
        {
            return (heap.at(buffer).address);
        }
        else
        {
            throw (std::runtime_error("Undefined reference to "+buffer+": undeclared variable"));
        }
    }
    else //It must be a value
    {
        return (parseValue(buffer));
    }
}

void Cc::eraseLine(std::string &data, const std::string &line)
{
    data.erase(data.find(line), line.length());
}

void Cc::dumpHeap(std::string &outputCode)
{
    for (auto it = heap.begin(); it != heap.end(); it++)
    {
        outputCode += it->second.value + "\n";
    }
}