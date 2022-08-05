#include "bitset_arithmetic.hh"

bool fullAdder(bool b1, bool b2, bool& carry)
{
    bool sum = (b1 ^ b2) ^ carry;
    carry = (b1 && b2) || (b1 && carry) || (b2 && carry);
    return sum;
}

void bitsetAdd(bitset &x, const bitset &y)
{
    bool carry = false;
    for (size_t i = 0; i < x.size(); ++i) {
        x[i] = fullAdder(x[i], y[i], carry);
    }
}

void bitsetSubtract(bitset &x, const bitset &y)
{
    bool borrow = false;
    for(int i = 0; i < x.size(); ++i) {
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

void bitsetMultiply(bitset &x, const bitset &y)
{
    bitset tmp = x;
    x.reset();
    if(tmp.count() < y.count()) {
        for(int i = 0; i < x.size(); ++i)
            if(tmp[i])
                bitsetAdd(x, y << i);
    } else {
        for(int i = 0; i < x.size(); ++i) {
            if(y[i])
                bitsetAdd(x, tmp << i);
        }
    }
}

bool bitsetLt(const bitset &x, const bitset &y)
{
    for(int i = x.size() - 1; i >= 0; --i) {
        if(x[i] && !y[i])
            return false;
        if(!x[i] && y[i])
            return true;
    }
    return false;
}

bool bitsetLtEq(const bitset &x, const bitset &y)
{
    for(int i = x.size() - 1; i >= 0; --i) {
        if(x[i] && !y[i]) 
            return false;
        if(!x[i] && y[i])
            return true;
    }
    return true;
}

void bitsetDivide(bitset x, bitset y,
                  bitset &q, bitset &r)
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
    for(int i = x.size() - 1; i >= 0; --i) {
        sig_x = i;
        if(x[i])
            break;
    }
    unsigned int sig_y;
    for(int i = x.size() - 1; i >= 0; --i) {
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

void RotLeft(bitset &set, unsigned long count)
{
    std::string substr(set.to_string());
    substr = substr.substr(0, count);
    bitset rotated(substr);
    set <<= count;
    set |= rotated;
}

void RotRight(bitset &set, unsigned long count)
{
    std::string substr(set.to_string());
    size_t len = substr.length();
    substr = substr.substr(len - count, count);
    bitset rotated(substr);
    rotated <<= len - count;
    set >>= count;
    set |= rotated;
}
