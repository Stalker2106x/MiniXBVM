#include "Electronic/Components.hh"

IC74LS161::IC74LS161()
: IC("IC74LS161", {
    {"Reset", Endpoint::Type::Input},
    {"Clock", Endpoint::Type::Input},
    {"P0", Endpoint::Type::Input},
    {"P1", Endpoint::Type::Input},
    {"P2", Endpoint::Type::Input},
    {"P3", Endpoint::Type::Input},
    {"EnableParallel", Endpoint::Type::Input},
    {"ParallelEnable", Endpoint::Type::Input},
    {"GND", Endpoint::Type::None},
    {"RippleCarryOut", Endpoint::Type::Output},
    {"Q0", Endpoint::Type::Output},
    {"Q1", Endpoint::Type::Output},
    {"Q2", Endpoint::Type::Output},
    {"Q3", Endpoint::Type::Output},
    {"EnableTrickle", Endpoint::Type::Input},
    {"Vcc", Endpoint::Type::None}
  })
{
}

void IC74LS161::function()
{

}