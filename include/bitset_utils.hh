#ifndef BITSET_UTILS_HH_
#define BITSET_UTILS_HH_

#include "bitset_arithmetic.hh"

template <wordSizeType SetSize, wordSizeType FinalSize>
std::bitset<FinalSize> bitsetRange(const std::bitset<SetSize> &a, unsigned int rangeStart, unsigned int rangeEnd)
{
  std::bitset<FinalSize> result;
  for (size_t i = rangeStart, j = 0; i < rangeEnd; i++, j++)
  {
    result[j] = a[i];
  }
  return (result);
}

template <wordSizeType SetSize, wordSizeType FinalSize>
std::bitset<FinalSize> bitsetPad(const std::bitset<SetSize> &a)
{
  std::bitset<FinalSize> result;
  for (size_t i = 0; i <= SetSize; i++)
  {
    result[i] = a[i];
  }
  return (result);
}

template <wordSizeType SetSize>
std::bitset<SetSize> bitsetConcat(const std::bitset<SetSize> &a, const std::bitset<SetSize> &b)
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

template <wordSizeType SetSize>
std::bitset<SetSize> bitsetErase(std::bitset<SetSize> a, unsigned int rangeStart, unsigned int rangeEnd)
{
  for (size_t i = rangeStart; i < rangeEnd; i++)
  {
    a[i] = 0;
  }
  return (a);
}

/***********************
 * OPERATORS OVERLOAD
 ***********************/

template <wordSizeType SetSize>
std::bitset<SetSize> operator+(std::bitset<SetSize> lhs, const std::bitset<SetSize> &rhs)
{
  bitsetAdd(lhs, rhs);
  return (lhs);
}

template <wordSizeType SetSize>
std::bitset<SetSize> operator-(std::bitset<SetSize> lhs, const std::bitset<SetSize> &rhs)
{
  bitsetSubtract(lhs, rhs);
  return (lhs);
}

template <wordSizeType SetSize>
std::bitset<SetSize> operator*(std::bitset<SetSize> lhs, const std::bitset<SetSize> &rhs)
{
  bitsetMultiply(lhs, rhs);
  return (lhs);
}

// template <wordSizeType SetSize>
// std::bitset<SetSize> operator/(const std::bitset<SetSize> &lhs, const std::bitset<SetSize> &rhs)
// {
//   return (bitsetDivide(lhs, rhs));
// }

template <wordSizeType SetSize>
std::bitset<SetSize> operator+=(std::bitset<SetSize> lhs, const std::bitset<SetSize>& rhs)
{
  lhs = lhs + rhs;
  return (lhs);
}

template <wordSizeType SetSize>
std::bitset<SetSize> operator++(std::bitset<SetSize>& rhs)
{
  rhs = rhs + std::bitset<SetSize>(0b1);
  return (rhs);
}

template <wordSizeType SetSize>
bool operator<(const std::bitset<SetSize> &lhs, const std::bitset<SetSize>& rhs)
{
  return (lhs.to_ullong() < rhs.to_ullong());
}

template <wordSizeType SetSize>
bool operator>(const std::bitset<SetSize> &lhs, const std::bitset<SetSize>& rhs)
{
  return (!(lhs < rhs));
}


#endif /* BITSET_UTILS_HH_ */