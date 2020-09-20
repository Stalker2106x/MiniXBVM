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
    if (carry) result.flip(); //overflow, set to NULL
    return (result);
  }

};

#endif /* !ARITHMETIC_HH_ */