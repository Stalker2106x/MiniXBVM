#include "Computer/Register.hh"

Register::Register(const int regSize) : _regSize(regSize), _data(regSize, 0)
{

}

Register::Register(const bitset data)
: _regSize(data.size()), _data(data)
{

}

void Register::write(const bitset value)
{
    _data = value;
}

const bitset Register::read() const
{
    return (_data);
}

void Register::clear()
{
    _data = bitset(_regSize, 0);
}

/**
 * OVERLOAD
 */


Register Register::operator=(Register& rhs)
{
    _data = rhs.read();
    return (*this);
}

Register Register::operator+=(Register& rhs)
{
    _data = _data + rhs._data;
    return (*this);
}

Register Register::operator++()
{
    _data = _data + bitset(_regSize, 1);
    return (*this);
}

Register Register::operator-=(const Register& rhs)
{
    _data = _data - rhs._data;
    return (*this);
}

Register Register::operator*=(const Register& rhs)
{
    _data = _data * rhs._data;
    return (*this);
}

Register Register::operator+(const Register& rhs) const
{
    return (_data + rhs.read());
}

Register Register::operator-(const Register& rhs) const
{
    return (_data - rhs.read());
}

Register Register::operator*(const Register& rhs) const
{
    return (_data * rhs.read());
}

Register Register::operator+(const bitset& rhs)
{
    _data = (_data + rhs);
    return (*this);
}

Register Register::operator-(const bitset& rhs)
{
    _data = (_data - rhs);
    return (*this);
}

Register Register::operator*(const bitset& rhs)
{
    _data = (_data * rhs);
    return (*this);
}