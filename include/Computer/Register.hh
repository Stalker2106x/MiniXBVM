#ifndef REGISTER_HH_
#define REGISTER_HH_

#include <unordered_map>
#include <array>
#include <bitset>
#include "config.h"
#include "bitset_utils.hh"

class Register
{
public:
  Register();
  Register(const bitset data);

  void write(const bitset value);

  const bitset read() const;

  void clear();

private:
  bitset _data;

  /*********************
  ** OPERATORS OVERLOAD
  *********************/
public:
  Register operator=(Register& rhs);
  Register operator+=(Register& rhs);
  Register operator++();
  Register operator-=(const Register& rhs);
  Register operator*=(const Register& rhs);
  Register operator+(const Register& rhs) const;
  Register operator-(const Register& rhs) const;
  Register operator*(const Register& rhs) const;
  Register operator+(const bitset& rhs);
  Register operator-(const bitset& rhs);
  Register operator*(const bitset& rhs);
};

#endif /* !REGISTER_HH_ */