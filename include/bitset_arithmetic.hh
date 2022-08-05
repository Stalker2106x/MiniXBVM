#ifndef BITSET_ARITHMETIC_HH_
#define BITSET_ARITHMETIC_HH_

#include <stdexcept>
#include <bitset>
#include "config.h"

bool fullAdder(bool b1, bool b2, bool& carry);

void bitsetAdd(bitset &x, const bitset &y);

void bitsetSubtract(bitset &x, const bitset &y);

void bitsetMultiply(bitset &x, const bitset &y);

bool bitsetLt(const bitset &x, const bitset &y);

bool bitsetLtEq(const bitset &x, const bitset &y);

void bitsetDivide(bitset x, bitset y, bitset &q, bitset &r);

void RotLeft(bitset &set, unsigned long count);

void RotRight(bitset &set, unsigned long count);

#endif /* !BITSET_ARITHMETIC_HH_ */