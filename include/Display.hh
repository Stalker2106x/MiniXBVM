#ifndef DISPLAY_HH_
#define DISPLAY_HH_

#include "Register.hh"

class Display
{
public:
  template <unsigned int WordSize>
  void render(std::string label, Register<1, WordSize> outputReg)
  {
    std::cout << label << ":" << outputReg.read() << std::endl;
  }

  void print(std::string msg)
  {
    std::cout << msg << std::endl;
  }
};

#endif /* !DISPLAY_HH_ */