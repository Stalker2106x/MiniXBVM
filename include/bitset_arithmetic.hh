#ifndef BITSET_ARITHMETIC_HH_
#define BITSET_ARITHMETIC_HH_

#include <stdexcept>
#include <bitset>
#include "config.h"

bool fullAdder(bool b1, bool b2, bool& carry);

template<wordSizeType SetSize>
void bitsetAdd(std::bitset<SetSize> &x, const std::bitset<SetSize> &y)
{
    bool carry = false;
    for (size_t i = 0; i < SetSize; ++i) {
        x[i] = fullAdder(x[i], y[i], carry);
    }
}

template<wordSizeType SetSize>
void bitsetSubtract(std::bitset<SetSize> &x, const std::bitset<SetSize> &y)
{
    bool borrow = false;
    for(int i = 0; i < SetSize; ++i) {
        if(borrow) {
            if(x[i]) {
                x[i] = y[i];
                borrow = y[i];
            } else {
                x[i] = !y[i];
                borrow = true;
            }
        } else {
            if(x[i]) {
                x[i] = !y[i];
                borrow = false;
            } else {
                x[i] = y[i];
                borrow = y[i];
            }
        }
    }
}

template<wordSizeType SetSize>
void bitsetMultiply(std::bitset<SetSize> &x, const std::bitset<SetSize> &y)
{
    std::bitset<SetSize> tmp = x;
    x.reset();
    if(tmp.count() < y.count()) {
        for(int i = 0; i < SetSize; ++i)
            if(tmp[i])
                bitsetAdd(x, y << i);
    } else {
        for(int i = 0; i < SetSize; ++i) {
            if(y[i])
                bitsetAdd(x, tmp << i);
        }
    }
}

template<wordSizeType SetSize>
bool bitsetLt(const std::bitset<SetSize> &x, const std::bitset<SetSize> &y)
{
    for(int i = SetSize - 1; i >= 0; --i) {
        if(x[i] && !y[i])
            return false;
        if(!x[i] && y[i])
            return true;
    }
    return false;
}

template<wordSizeType SetSize>
bool bitsetLtEq(const std::bitset<SetSize> &x, const std::bitset<SetSize> &y)
{
    for(int i = SetSize - 1; i >= 0; --i) {
        if(x[i] && !y[i]) 
            return false;
        if(!x[i] && y[i])
            return true;
    }
    return true;
}

template<wordSizeType SetSize>
void bitsetDivide(std::bitset<SetSize> x, std::bitset<SetSize> y,
                  std::bitset<SetSize> &q, std::bitset<SetSize> &r)
{
    if(y.none())
        throw std::domain_error("division by zero!");
    q.reset();
    r.reset();
    if(x.none())
        return;
    if(x == y) {
        q[0] = 1;
        return;
    }
    r = x;
    if(bitsetLt(x, y))
        return;
    unsigned int sig_x;
    for(int i = SetSize - 1; i >= 0; --i) {
        sig_x = i;
        if(x[i])
            break;
    }
    unsigned int sig_y;
    for(int i = SetSize - 1; i >= 0; --i) {
        sig_y = i;
        if(y[i])
            break;
    }
    unsigned int n = sig_x - sig_y;
    y <<= n;
    n++;
    while(n--) {
       if(bitsetLtEq(y,r)) {
           q[n] = true;
           bitsetSubtract(r, y);
       }
       y >>= 1;
    }
}

template<wordSizeType SetSize>
void RotLeft(std::bitset<SetSize> &bitset, unsigned long count)
{
    std::string substr(bitset.to_string());
    substr = substr.substr(0, count);
    std::bitset<SetSize> rotated(substr);
    bitset <<= count;
    bitset |= rotated;
}

template<wordSizeType SetSize>
void RotRight(std::bitset<SetSize> &bitset, unsigned long count)
{
    std::string substr(bitset.to_string());
    size_t len = substr.length();
    substr = substr.substr(len - count, count);
    std::bitset<SetSize> rotated(substr);
    rotated <<= len - count;
    bitset >>= count;
    bitset |= rotated;
}

#endif /* !BITSET_ARITHMETIC_HH_ */