#include "Computer/Memory.hh"
#include "bitset_utils.hh"
#include "App.hh"

Memory::Memory()
{
    bitset lastAddress = bitset(App::instance->config.ramAddrBitsize, getSize()-1);

    for (bitset it = bitset(App::instance->config.ramAddrBitsize, 0); it < lastAddress; ++it)
    {
        _data.emplace(it, Register(App::instance->config.ramDataBitsize));
    }
}

void Memory::write(const bitset address, const bitset value)
{
    _data.at(address).write(value);
}

const bitset Memory::read(const bitset address) const
{
    return (_data.at(address).read());
}

void Memory::clear()
{
    bitset lastAddress = bitset(App::instance->config.ramAddrBitsize, getSize()-1);

    for (bitset it = bitset(App::instance->config.ramAddrBitsize, 0); it < lastAddress; ++it)
    {
        _data.at(it).clear();
    }
}

size_t Memory::getSize() const
{
    return (pow(2, App::instance->config.ramAddrBitsize));
}

size_t Memory::getUsedSize() const
{
    size_t size = 0;
    for (auto rit = _data.rbegin(); rit != _data.rend(); ++rit)
    {
        if (rit->second.read().any()) return (std::distance(_data.begin(), rit.base()));
    }
    return (0);
}

Register Memory::operator[](bitset address) const
{
    return (_data.at(address));
}

std::map<bitset, Register> Memory::read() const
{
    return (_data);
}