#include "Computer/Memory.hh"
#include "bitset_utils.hh"

Memory::Memory(const int addrSize, const int regSize) : _addrSize(addrSize), _regSize(regSize)
{
    bitset lastAddress = bitset(addrSize, getSize()-1);

    for (bitset it = bitset(addrSize, 0); it < lastAddress; ++it)
    {
        _data.emplace(it, Register(regSize));
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
    bitset lastAddress = bitset(_addrSize, getSize()-1);

    for (bitset it = bitset(_addrSize, 0); it < lastAddress; ++it)
    {
        _data.at(it).clear();
    }
}

size_t Memory::getSize() const
{
    return (pow(2, _addrSize));
}

size_t Memory::getUsedSize() const
{
    size_t size = 0;
    bitset emptyReg = bitset(_regSize, 0);
    for (auto it = _data.begin(); it != _data.end(); ++it)
    {
        if (it->second.read() != emptyReg) size += 1;
    }
    return (size);
}

Register Memory::operator[](bitset address) const
{
    return (_data.at(address));
}

std::unordered_map<bitset, Register, BitsetHash> Memory::read() const
{
    return (_data);
}