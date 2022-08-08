#include "bitset_utils.hh"
#include <iostream>

bitset bitsetRange(const bitset &a, unsigned int rangeStart, unsigned int rangeEnd)
{
  bitset result = bitset(rangeEnd-rangeStart, 0);
  for (size_t i = rangeStart, resIt = 0; i < rangeEnd; i++, resIt++)
  {
    result[resIt] = a[i];
    std::cout << result.to_string() << "b" << a[i] << std::endl;
  }
  return (result);
}

bitset bitsetPad(const bitset &a)
{
  bitset result = bitset(a.size(), 0);
  for (size_t i = 0; i <= a.size(); i++)
  {
    result[i] = a[i];
  }
  return (result);
}

bitset bitsetConcat(const bitset &a, const bitset &b)
{
  bitset result = bitset(a.size()+b.size(), 0);
  size_t resIt = 0;
  for (size_t i = 0; i < a.size(); i++)
  {
    result[resIt++] = a[i];
  }
  for (size_t i = 0; i < b.size(); i++)
  {
    result[resIt++] = b[i];
  }
  return (result);
}

bitset bitsetErase(bitset a, unsigned int rangeStart, unsigned int rangeEnd)
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

bitset operator+(bitset lhs, const bitset &rhs)
{
  bitsetAdd(lhs, rhs);
  return (lhs);
}

bitset operator+(bitset lhs, const size_t &rhs)
{
  lhs = lhs + bitset(lhs.size(), rhs);
  return (lhs);
}

bitset operator-(bitset lhs, const bitset &rhs)
{
  bitsetSubtract(lhs, rhs);
  return (lhs);
}

bitset operator*(bitset lhs, const bitset &rhs)
{
  bitsetMultiply(lhs, rhs);
  return (lhs);
}

// bitset operator/(const bitset &lhs, const bitset &rhs)
// {
//   return (bitsetDivide(lhs, rhs));
// }

bitset operator+=(bitset lhs, const bitset& rhs)
{
  lhs = lhs + rhs;
  return (lhs);
}

bitset operator+=(bitset lhs, const size_t& rhs)
{
  lhs = lhs + rhs;
  return (lhs);
}

bitset operator++(bitset& lhs)
{
  lhs = lhs + 1;
  return (lhs);
}
