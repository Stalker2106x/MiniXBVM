#include <iostream>
#include "Computer.hh"

Computer::Computer()
{
  _RAM.write(word(0b0000), dword(0b00000000));
  _RAM.write(word(0b0001), dword(0b11110000));

  _PC.write(word(0b0000));
}

void Computer::cycle()
{
  _MAR = _PC;
  ++_PC;
  _IR.write(_RAM[_MAR.read()].read()); //Rea)d the current instruction and store it in instruction registr

  _display << "PC" << _PC;
  _display << "MAR" << _MAR;
  _display << "IR" << _IR;
  execute();
  _display << "OUT" << _output;
}

void Computer::execute()
{
  switch ((Arithmetic::range<DWORD_SIZE, WORD_SIZE>(_IR.read(), 0, WORD_SIZE-1)).to_ulong())
  {
    case OP_LDA:
      _MAR.write(Arithmetic::range<DWORD_SIZE, WORD_SIZE>(_IR.read(), WORD_SIZE-1, DWORD_SIZE-1)); //Extract adress from IR
      _accumulator.write(_RAM[_MAR.read()].read());
      break;
    case OP_ADD:
      _MAR.write(Arithmetic::range<DWORD_SIZE, WORD_SIZE>(_IR.read(), WORD_SIZE-1, DWORD_SIZE-1)); //Extract adress from IR
      _Breg.write(_RAM[_MAR.read()].read());
      _accumulator += _Breg;
      break;
    case OP_SUB:
      _MAR.write(Arithmetic::range<DWORD_SIZE, WORD_SIZE>(_IR.read(), WORD_SIZE-1, DWORD_SIZE-1)); //Extract adress from IR
      _Breg.write(_RAM[_MAR.read()].read());
      _accumulator -= _Breg;
      break;
    case OP_OUT:
      _output.write(_accumulator.read()); //Extract acc to output
      break;
    case OP_HLT:
      exit(0);
      break;
    default:
      _display << "ERROR";
      break;
  }
}