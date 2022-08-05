#ifndef MEMORY_HH_
#define MEMORY_HH_

#include <algorithm>
#include <unordered_map>
#include <vector>
#include <bitset>
#include <cmath>
#include "Computer/Register.hh"
#include "utils.hh"

class Memory
{
public:
  Memory(const int addrSize, const int regSize);

  void write(const bitset address, const bitset value);
  const bitset read(const bitset address) const;
  void clear();
  size_t getSize() const;
  size_t getUsedSize() const;
  Register operator[](bitset address) const;
  std::unordered_map<bitset, Register, BitsetHash> read() const;

private:
  int _addrSize;
  int _regSize;
  std::unordered_map<bitset, Register, BitsetHash> _data;
};

#endif /* !MEMORY_HH_ */