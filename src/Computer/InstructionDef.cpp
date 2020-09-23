#include "Cc/InstructionDef.hh"
#include "Computer/Computer.hh"

void LDAExecutor(Computer &computer)
{
    computer._MAR.write(Arithmetic::range<DWORD_SIZE, WORD_SIZE>(computer._IR.read(), 0, WORD_SIZE));//Extract adress from IR
    computer._accumulator.write(Arithmetic::erase(computer._RAM[computer._MAR.read()].read(), WORD_SIZE, DWORD_SIZE));
}

void ADDExecutor(Computer &computer)
{
    computer._MAR.write(Arithmetic::range<DWORD_SIZE, WORD_SIZE>(computer._IR.read(), 0, WORD_SIZE));//Extract adress from IR
    computer._Breg.write(Arithmetic::erase(computer._RAM[computer._MAR.read()].read(), WORD_SIZE, DWORD_SIZE));
    computer._accumulator += computer._Breg;
}

void SUBExecutor(Computer &computer)
{
    computer._MAR.write(Arithmetic::range<DWORD_SIZE, WORD_SIZE>(computer._IR.read(), 0, WORD_SIZE));//Extract adress from IR
    computer._Breg.write(Arithmetic::erase(computer._RAM[computer._MAR.read()].read(), WORD_SIZE, DWORD_SIZE));
    computer._accumulator -= computer._Breg;
}

void OUTExecutor(Computer &computer)
{
    computer._output.write(computer._accumulator.read()); //Extract acc to output
}


void HLTExecutor(Computer &computer)
{
    computer.halt();
}