#ifndef DISPLAY_HH_
#define DISPLAY_HH_

#include "Computer/Register.hh"

class Display
{
public:
  template <typename T>
  Display &operator<<(T ent)
  {
    std::cout << ent;
    return (*this);
  }

  template <wordSizeType RegSize>
  Display &operator<<(Register<RegSize> reg)
  {
    return (*this << reg.read());
  }
};


#endif /* !DISPLAY_HH_ */