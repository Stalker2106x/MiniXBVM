#ifndef MEMORY_HH_
#define MEMORY_HH_

#include <unordered_map>
#include <bitset>
#include "Arithmetic.hh"

template <wordSizeType AddrSize, wordSizeType RegSize>
class Memory
{
public:

  void write(const std::bitset<AddrSize> address, const std::bitset<RegSize> value)
  {
    _data[address].write(value);
  }

  const std::bitset<RegSize> read(const std::bitset<AddrSize> address)
  {
    return (_data[address].read());
  }

  void clear()
  {
    _data.clear();
  }

  Register<RegSize> operator[](std::bitset<AddrSize> address)
  {
    return (_data[address]);
  }

private:
  std::unordered_map<std::bitset<AddrSize>, Register<RegSize>> _data;
};

#endif /* !MEMORY_HH_ */