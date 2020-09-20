#ifndef REGISTER_HH_
#define REGISTER_HH_

#include <array>
#include <bitset>

template <unsigned int RegSize, unsigned int WordSize>
class Register
{
public:
  void write(const std::bitset<WordSize> value, unsigned int index = 0)
  {
    _data[index] = value;
  }

  // void add(const std::bitset<WordSize> value, unsigned int index = 0)
  // {
  //   _data[index] += value;
  // }

  const std::bitset<WordSize> read(unsigned int index = 0)
  {
    return (_data[index]);
  }

  void clear()
  {
    std::fill(_data.begin(), _data.end(), std::bitset<WordSize>(0));
  }

private:
  std::array<std::bitset<WordSize>, RegSize> _data;
};

#endif /* !REGISTER_HH_ */