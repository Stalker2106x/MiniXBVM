#ifndef RAMINSPECTOR_HH_
#define RAMINSPECTOR_HH_

#include "utils.hh"

class RamInspector
{
public:
    RamInspector();

    void update();
    void draw();

private:
    size_t _memorySize, _memoryUsedSize;
    std::vector<std::pair<std::string, std::string>> _ramDump;
    Base _addrBase;
    Base _valueBase;
};

#endif /* !RAMINSPECTOR_HH_ */