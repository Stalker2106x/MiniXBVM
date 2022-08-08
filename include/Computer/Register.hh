#ifndef REGISTER_HH_
#define REGISTER_HH_

#include <bitset>
#include "config.h"
#include "bitset_utils.hh"

class Register
{
public:
  Register(const size_t regSize);
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
  Register operator=(const Register& rhs);
  Register operator+=(const Register& rhs);
  Register operator+=(const size_t& rhs);
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