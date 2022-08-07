#include "Computer/Register.hh"
#include "App.hh"

Register::Register() : _data(App::instance->config.ramDataBitsize, 0)
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
    _data = _data + bitset(App::instance->config.ramDataBitsize, 1);
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