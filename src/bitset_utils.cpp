#include "bitset_utils.hh"

bitset bitsetRange(const bitset &a, unsigned int rangeStart, unsigned int rangeEnd)
{
  bitset result;
  for (size_t i = rangeStart, j = 0; i < rangeEnd; i++, j++)
  {
    result[j] = a[i];
  }
  return (result);
}

bitset bitsetPad(const bitset &a)
{
  bitset result;
  for (size_t i = 0; i <= a.size(); i++)
  {
    result[i] = a[i];
  }
  return (result);
}

bitset bitsetConcat(const bitset &a, const bitset &b)
{
  bitset result;
  for (size_t i = 1; i <= 2; i++)
  {
    for (size_t j = 0; j < a.size(); j++)
    {
      result[i * j] = a[j];
    }
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

bitset operator++(bitset& rhs)
{
  rhs = rhs + bitset(rhs.size(), 0b1);
  return (rhs);
}
