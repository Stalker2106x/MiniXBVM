#ifndef MEMORY_HH_
#define MEMORY_HH_

#include <algorithm>
#include <unordered_map>
#include <vector>
#include <bitset>
#include <cmath>
#include "Computer/Register.hh"

template <wordSizeType AddrSize, wordSizeType RegSize>
class Memory
{
public:
  Memory()
  {
    std::bitset<AddrSize> lastAddress = std::bitset<AddrSize>(getSize()-1);

    for (std::bitset<AddrSize> it = std::bitset<AddrSize>(0); it < lastAddress; ++it)
    {
      _data.emplace(it, Register<RegSize>());
    }
  }

  void write(const std::bitset<AddrSize> address, const std::bitset<RegSize> value)
  {
    _data[address].write(value);
  }

  const std::bitset<RegSize> read(const std::bitset<AddrSize> address) const
  {
    return (_data[address].read());
  }

  void clear()
  {
    std::for_each(_data.begin(), _data.end(), [&](std::pair<std::bitset<AddrSize>, Register<RegSize>> item) { item.second.clear(); });
  }

  size_t getSize() const
  {
    return (pow(2, AddrSize));
  }

  size_t getUsedSize() const
  {
    size_t size = 0;
    std::bitset<RegSize> emptyReg = std::bitset<RegSize>(0);
    for (auto it = _data.begin(); it != _data.end(); it++)
    {
      if (it->second.read() != emptyReg) size += 1;
    }
    return (size);
  }

  Register<RegSize> operator[](std::bitset<AddrSize> address) const
  {
    return (_data.at(address));
  }

  std::unordered_map<std::bitset<AddrSize>, Register<RegSize>> read() const
  {
    return (_data);
  }

private:
  std::unordered_map<std::bitset<AddrSize>, Register<RegSize>> _data;
};

#endif /* !MEMORY_HH_ */