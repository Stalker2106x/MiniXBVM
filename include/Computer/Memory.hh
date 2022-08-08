#ifndef MEMORY_HH_
#define MEMORY_HH_

#include <algorithm>
#include <map>
#include <vector>
#include <bitset>
#include <cmath>
#include "Computer/Register.hh"
#include "utils.hh"

class Memory
{
public:
  Memory();

  void write(const bitset address, const bitset value);
  const bitset read(const bitset address) const;
  void clear();
  size_t getSize() const;
  size_t getUsedSize() const;
  Register operator[](bitset address) const;
  std::map<bitset, Register> read() const;

private:
  std::map<bitset, Register> _data;
};

#endif /* !MEMORY_HH_ */