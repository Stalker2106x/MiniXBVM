#ifndef REGISTER_HH_
#define REGISTER_HH_

#include <unordered_map>
#include <array>
#include <bitset>
#include "config.h"
template <wordSizeType RegSize>
class Register
{
public:
  Register() {};
  Register(const std::bitset<RegSize> data)
  : _data(data)
  {};

  void write(const std::bitset<RegSize> value)
  {
    _data = value;
  }

  const std::bitset<RegSize> read() const
  {
    return (_data);
  }

  void clear()
  {
    _data = std::bitset<RegSize>(0);
  }

private:
  std::bitset<RegSize> _data;

  /*********************
  ** OPERATORS OVERLOAD
  *********************/
public:
  Register<RegSize> operator=(Register<RegSize>& rhs)
  {
    _data = rhs.read();
    return (*this);
  }

  Register<RegSize> operator+=(Register<RegSize>& rhs)
  {
    _data = _data + rhs._data;
    return (*this);
  }

  Register<RegSize> operator++()
  {
    _data = _data + std::bitset<RegSize>(0b1);
    return (*this);
  }

  Register<RegSize> operator-=(const Register<RegSize>& rhs)
  {
    _data = _data - rhs._data;
    return (*this);
  }

  Register<RegSize> operator*=(const Register<RegSize>& rhs)
  {
    _data = _data * rhs._data;
    return (*this);
  }

  Register<RegSize> operator+(const Register<RegSize>& rhs) const
  {
    return (_data + rhs.read());
  }

  Register<RegSize> operator-(const Register<RegSize>& rhs) const
  {
    return (_data - rhs.read());
  }

  Register<RegSize> operator*(const Register<RegSize>& rhs) const
  {
    return (_data * rhs.read());
  }

  Register<RegSize> operator+(const std::bitset<RegSize>& rhs) const
  {
    _data = (_data + rhs);
    return (*this);
  }

  Register<RegSize> operator-(const std::bitset<RegSize>& rhs) const
  {
    _data = (_data - rhs);
    return (*this);
  }
  
  Register<RegSize> operator*(const std::bitset<RegSize>& rhs) const
  {
    _data = (_data * rhs);
    return (*this);
  }
};

#endif /* !REGISTER_HH_ */