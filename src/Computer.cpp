#include <iostream>
#include "Computer.hh"

Computer::Computer()
{
  _programCounter.write(std::bitset<WORD_SIZE>(0b0000));
}

void Computer::cycle()
{
  std::cout << "PC: " << _programCounter.read() << std::endl;
  //END CYCLE
}