#include <bitset>
#include "utils.hh"

long long int int128FromString(std::string str)
{
  if (str.length() > 1)
  {
    std::string value = str.substr(2, str.length());
    if (str[0] == '0' && str[1] == HEX_DELIM)
    {
      if (value.find_first_not_of("0123456789ABCDEF") != std::string::npos) throw (std::runtime_error("Invalid HEX string"));
      std::stringstream ss;
      long long int res;
      ss << std::hex << value;
      ss >> res;
      return (res);
    }
    else if (str[0] == '0' && str[1] == BIN_DELIM)
    {
      if (value.find_first_not_of("01") != std::string::npos) throw (std::runtime_error("Invalid BIN string"));
      return (std::bitset<sizeof(long long int)>(value).to_ullong());
    }
  }
  if (str.find_first_not_of("0123456789") != std::string::npos) throw (std::runtime_error("Invalid INT string"));
  std::stringstream ss;
  long long int res;
  ss << str;
  ss >> res;
  return (res);
}

std::string baseToLabel(Base base)
{
  if (base == Base::Bin) return ("Bin");
  else if (base == Base::Oct) return ("Oct");
  else if (base == Base::Hex) return ("Hex");
  else if (base == Base::Dec) return ("Dec");
  else if (base == Base::ASCII) return ("ASCII");
  else return ("?");
}