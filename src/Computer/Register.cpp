#include "Computer/Register.hh"
#include "App.hh"

Register::Register(const size_t regSize) : _data(regSize, 0)
{
}

Register::Register(const bitset data)
: _data(data)
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
    _data.reset();
}

/**
 * OVERLOAD
 */


Register Register::operator=(const Register& rhs)
{
    _data = rhs.read();
    return (*this);
}

Register Register::operator+=(const Register& rhs)
{
    _data = _data + rhs._data;
    return (*this);
}

Register Register::operator+=(const size_t& rhs)
{
    _data = _data + rhs;
    return (*this);
}

Register Register::operator++()
{
    _data = _data + bitset(_data.size(), 1);
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