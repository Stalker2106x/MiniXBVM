#ifndef ARITHMETIC_HH_
#define ARITHMETIC_HH_

#include <iostream>

class Arithmetic
{
public:
  template <unsigned int WordSize>
  static std::bitset<WordSize> add(std::bitset<WordSize> a, std::bitset<WordSize> b)
  {
    std::bitset<WordSize> result;
    bool carry = false;
    for (size_t i = 0; i < WordSize; i++)
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
  
  template <unsigned int WordSize>
  static std::bitset<WordSize> substract(std::bitset<WordSize> a, std::bitset<WordSize> b)
  {
    std::bitset<WordSize> result;
    bool carry = false;
    for (size_t i = 0; i < WordSize; i++)
    {
      //NI
    }
    return (result);
  }

  template <unsigned int WordSize, unsigned int FinalSize>
  static std::bitset<FinalSize> range(std::bitset<WordSize> a, unsigned int rangeStart, unsigned int rangeEnd)
  {
    std::bitset<FinalSize> result;
    for (size_t i = rangeStart, j = 0; i < rangeEnd; i++, j++)
    {
      result[j] = a[i];
    }
    return (result);
  }

  template <unsigned int WordSize, unsigned int FinalSize>
  static std::bitset<FinalSize> pad(std::bitset<WordSize> a)
  {
    std::bitset<FinalSize> result;
    for (size_t i = 0; i <= WordSize; i++)
    {
      result[i] = a[i];
    }
    return (result);
  }

  template <unsigned int WordSize>
  static std::bitset<WordSize> concat(std::bitset<WordSize> a, std::bitset<WordSize> b)
  {
    std::bitset<WordSize> result;
    for (size_t i = 1; i <= 2; i++)
    {
      for (size_t j = 0; j < WordSize; j++)
      {
        result[i * j] = a[j];
      }
    }
    return (result);
  }

};

#endif /* !ARITHMETIC_HH_ */