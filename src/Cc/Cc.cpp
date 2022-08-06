#include <sstream>
#include <stdexcept>
#include <algorithm>
#include "Cc/Cc.hh"
#include "Cc/InstructionDef.hh"
#include "utils.hh"

std::string Cc::compile(std::string buffer, bool &validMachineProgram)
{
    int lineNumber = 1;
    std::istringstream iss(buffer);
    std::string errOutput;
    std::string output;
    std::string line;

    while(std::getline(iss, line, '\n'))
    {
        try {
            if (line.empty()) continue; //Skip empty line
            std::istringstream lss(line);
            std::string buffer;
            //Parse first word (usually instruction)
            lss >> buffer;
            auto instructionsIt = std::find_if(instructionsSet.begin(), instructionsSet.end(), [&buffer] (InstructionDef def) { return (def.name == buffer); } );
            if (instructionsIt == instructionsSet.end())
            {
                //Instruction was not found, we consider that it is raw data
                try {
                    output += parseData(buffer);
                } catch(...) {
                    //It is not raw data either, its probably garbage...
                    throw (std::runtime_error("instruction "+buffer+" is unknown or invalid"));
                }
            }
            output += instructionsIt->code.to_string();
            //Parse remaining line if any
            int operandsFound = 0;
            while (lss.tellg() != -1)
            {
                if (lss >> buffer)
                {
                    output += parseData(buffer);
                    operandsFound += 1;
                }
            }
            if (instructionsIt->operandCount != operandsFound)
            {
                throw (std::runtime_error("instruction "+instructionsIt->name+" expects "+std::to_string(instructionsIt->operandCount)+" operands, "+std::to_string(operandsFound)+" found."));
            }
            output += '\n';
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

std::string Cc::parseData(const std::string &buffer)
{
    try {
        return (bitsetToString(Base::Bin, bitset(DWORD_SIZE, intFromString(buffer))));
    } catch (...) {
        throw (std::runtime_error("failed to parse operand "+buffer+": invalid integer"));
    }
}