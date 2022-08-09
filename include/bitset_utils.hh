#ifndef BITSET_UTILS_HH_
#define BITSET_UTILS_HH_

#include "config.h"
#include "bitset_arithmetic.hh"

bitset bitsetRange(const bitset &a, unsigned int rangeStart, unsigned int rangeEnd);
bitset bitsetPad(const bitset &a);
bitset bitsetConcat(const bitset &a, const bitset &b);
bitset bitsetErase(bitset a, unsigned int rangeStart, unsigned int rangeEnd);

/***********************
 * OPERATORS OVERLOAD
 ***********************/

bitset operator+(bitset lhs, const bitset &rhs);
bitset operator+(bitset lhs, const size_t &rhs);
bitset operator-(bitset lhs, const bitset &rhs);
bitset operator*(bitset lhs, const bitset &rhs);
// bitset operator/(const bitset &lhs, const bitset &rhs);
bitset operator+=(bitset lhs, const bitset& rhs);
bitset operator+=(bitset lhs, const size_t &rhs);
bitset operator++(bitset& rhs);


#endif /* BITSET_UTILS_HH_ */