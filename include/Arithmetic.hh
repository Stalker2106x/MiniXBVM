#ifndef ARITHMETIC_HH_
#define ARITHMETIC_HH_

#include <iostream>
#include "config.h"

class Arithmetic
{
public:
  template <wordSizeType SetSize>
  static std::bitset<SetSize> add(const std::bitset<SetSize> &a, const std::bitset<SetSize> &b)
  {
    std::bitset<SetSize> result;
    bool carry = false;
    for (size_t i = 0; i < SetSize; i++)
    {
      if (a[i] & b[i]) // 1 & 1
      {
        if (carry) result[i] = 1; //Discard old carry
        carry = true; //Set carry
      }
      else if (a[i] | b[i]) // 0 & 1 or 1 & 0
      {
        if (!carry) result[i] = 1; //Do sum
        //else continue with carry
      }
      else // 0 & 0
      {
        if (carry)
        {
          result[i] = 1;
          carry = false;
        }
      }
    }
    return (result);
  }
  
  template <wordSizeType SetSize>
  static std::bitset<SetSize> substract(const std::bitset<SetSize> &a, const std::bitset<SetSize> &b)
  {
    std::bitset<SetSize> result;
    bool carry = false;
    for (size_t i = 0; i < SetSize; i++)
    {
      //NI
    }
    return (result);
  }

  template <wordSizeType SetSize, wordSizeType FinalSize>
  static std::bitset<FinalSize> range(const std::bitset<SetSize> &a, unsigned int rangeStart, unsigned int rangeEnd)
  {
    std::bitset<FinalSize> result;
    for (size_t i = rangeStart, j = 0; i < rangeEnd; i++, j++)
    {
      result[j] = a[i];
    }
    return (result);
  }

  template <wordSizeType SetSize, wordSizeType FinalSize>
  static std::bitset<FinalSize> pad(const std::bitset<SetSize> &a)
  {
    std::bitset<FinalSize> result;
    for (size_t i = 0; i <= SetSize; i++)
    {
      result[i] = a[i];
    }
    return (result);
  }

  template <wordSizeType SetSize>
  static std::bitset<SetSize> concat(const std::bitset<SetSize> &a, const std::bitset<SetSize> &b)
  {
    std::bitset<SetSize> result;
    for (size_t i = 1; i <= 2; i++)
    {
      for (size_t j = 0; j < SetSize; j++)
      {
        result[i * j] = a[j];
      }
    }
    return (result);
  }

};

template <wordSizeType SetSize>
std::bitset<SetSize> operator+(std::bitset<SetSize> lhs, std::bitset<SetSize> rhs)
{
  return (Arithmetic::add(lhs, rhs));
}

template <wordSizeType SetSize>
std::bitset<SetSize> operator-(std::bitset<SetSize> lhs, std::bitset<SetSize> rhs)
{
  return (Arithmetic::substract(lhs, rhs));
}

template <wordSizeType SetSize>
std::bitset<SetSize> operator+=(std::bitset<SetSize> lhs, std::bitset<SetSize>& rhs)
{
  lhs = lhs + rhs;
  return (lhs);
}

#endif /* !ARITHMETIC_HH_ */