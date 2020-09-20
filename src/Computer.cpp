#include <iostream>
#include "Computer.hh"

Computer::Computer()
{
  _RAM.write(std::bitset<DWORD_SIZE>(0b00001111), std::bitset<DWORD_SIZE>(0b00000000));
  _RAM.write(std::bitset<DWORD_SIZE>(0b01010101), std::bitset<DWORD_SIZE>(0b11110000));

  _PC.write(std::bitset<WORD_SIZE>(0b0000));
}

void Computer::cycle()
{
  _MAR.write(_PC.read());
  _PC.write(Arithmetic::add(_PC.read(), std::bitset<WORD_SIZE>(0b0001)));
  _IR.write(_RAM.read(Arithmetic::pad<WORD_SIZE, DWORD_SIZE>(_MAR.read()))); //Rea)d the current instruction and store it in instruction register

  _display.render("PC", _PC);
  _display.render("MAR", _MAR);
  _display.render("IR", _IR);
  execute();
  _display.render("OUT", _output);
}

void Computer::execute()
{
  switch ((Arithmetic::range<DWORD_SIZE, WORD_SIZE>(_IR.read(), 0, WORD_SIZE-1)).to_ulong())
  {
    case OP_LDA:
      _MAR.write(Arithmetic::range<DWORD_SIZE, WORD_SIZE>(_IR.read(), WORD_SIZE-1, DWORD_SIZE-1)); //Extract adress from IR
      _accumulator.write(_RAM.read(Arithmetic::pad<WORD_SIZE, DWORD_SIZE>(_MAR.read())));
      break;
    case OP_ADD:
      _MAR.write(Arithmetic::range<DWORD_SIZE, WORD_SIZE>(_IR.read(), WORD_SIZE-1, DWORD_SIZE-1)); //Extract adress from IR
      _Breg.write(_RAM.read(Arithmetic::pad<WORD_SIZE, DWORD_SIZE>(_MAR.read())));
      _accumulator.write(Arithmetic::add(_accumulator.read(), _Breg.read()));
      break;
    case OP_SUB:
      _MAR.write(Arithmetic::range<DWORD_SIZE, WORD_SIZE>(_IR.read(), WORD_SIZE-1, DWORD_SIZE-1)); //Extract adress from IR
      _accumulator.write(_RAM.read(Arithmetic::pad<WORD_SIZE, DWORD_SIZE>(_MAR.read())));
      _accumulator.write(Arithmetic::substract(_accumulator.read(), _Breg.read()));
      break;
    case OP_OUT:
      _output.write(_accumulator.read()); //Extract acc to output
      break;
    case OP_HLT:
      exit(0);
      break;
    default:
      _display.print("ERROR");
      break;
  }
}