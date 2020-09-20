#ifndef REGISTER_HH_
#define REGISTER_HH_

#include <unordered_map>
#include <array>
#include <bitset>
#include "Arithmetic.hh"

template <unsigned int RegSize, unsigned int WordSize>
class Register
{
public:
  void write(const std::bitset<WordSize> value, const std::bitset<WordSize> adress = std::bitset<WordSize>())
  {
    _data[adress] = value;
  }

  const std::bitset<WordSize> read(const std::bitset<WordSize> adress = std::bitset<WordSize>())
  {
    return (_data[adress, WordSize]);
  }

  void clear()
  {
    _data.clear();
  }

private:
  std::unordered_map<std::bitset<WordSize>, std::bitset<WordSize>> _data;
};

#endif /* !REGISTER_HH_ */