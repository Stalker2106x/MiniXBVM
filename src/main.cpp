#include <iostream>
#include "Computer.hh"
#include "Clock.hh"

int main(int argc, char **argv)
{
  Computer cpu;
  Clock clock;

  while (1)
  {
    clock.cycle();
    std::cout << "clock tick" << std::endl;
    cpu.cycle();
  }
  return (0);
}