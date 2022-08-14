#include <bitset>
#include "utils.hh"

long long int intFromString(Base stringBase, std::string str)
{
  if (stringBase == Base::Unknown) //Unknown base, need to detect
  {
    if (std::find_if(str.begin(), str.end(), not_hexadecimal()) == str.end()) stringBase = Base::Hex;
    else if (std::find_if(str.begin(), str.end(), not_decimal()) == str.end()) stringBase = Base::Dec;
    else if (std::find_if(str.begin(), str.end(), not_octal()) == str.end()) stringBase = Base::Oct;
    else if (std::find_if(str.begin(), str.end(), not_binary()) == str.end()) stringBase = Base::Bin;
    else throw (std::runtime_error("Unable to detect base of string"));
  }
  if (stringBase == Base::Hex)
  {
    if (str.find_first_not_of("0123456789ABCDEF") != std::string::npos) throw (std::runtime_error("Invalid HEX string"));
    std::stringstream ss;
    long long int res;
    ss << std::hex << str;
    ss >> res;
    return (res);
  }
  else if (stringBase == Base::Bin)
  {
    if (str.find_first_not_of("01") != std::string::npos) throw (std::runtime_error("Invalid BIN string"));
    return (std::bitset<sizeof(long long int)>(str).to_ullong());
  }
  else if (stringBase == Base::Oct)
  {
    throw (std::runtime_error("Not implemented"));
  }
  else //Dec
  {
    if (str.find_first_not_of("0123456789") != std::string::npos) throw (std::runtime_error("Invalid INT string"));
    std::stringstream ss;
    long long int res;
    ss << str;
    ss >> res;
    return (res);
  }
}

long long int bitsetToLong(bitset set)
{
  long long int res = 0;
  for (size_t b = 0; b < set.size(); b++)
  {
    if (set[b]) res += pow(2, b);
  }
  return (res);
}

std::string bitsetToString(Base base, bitset set, bool addSpaces)
{
    if (base == Base::ASCII) return (std::to_string(intFromString(Base::Bin, set.to_string())));
    std::stringstream ss;
    if (base == Base::Bin)
    {
        std::string str = set.to_string();
        for (int i = 0; i < str.size(); i++)
        {
            if (addSpaces && i != 0 && (i % 8 == 0))
            {
              ss << ' ';
            }
            ss << str[i];
        }
    }
    else //Dec, Hex, Oct
    {
        if (base == Base::Hex) ss << "0x" << std::hex;
        if (base == Base::Oct) ss << "0" << std::oct;
        ss << std::uppercase << intFromString(Base::Bin, set.to_string());
    }
    return (ss.str());
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