#include "Electronic/Components.hh"

IC74LS161::IC74LS161()
: IC("IC74LS161", {
    {"RST", Endpoint::Type::Input},
    {"CLK", Endpoint::Type::Input},
    {"P0", Endpoint::Type::Input},
    {"P1", Endpoint::Type::Input},
    {"P2", Endpoint::Type::Input},
    {"P3", Endpoint::Type::Input},
    {"CEP", Endpoint::Type::Input},
    {"GND", Endpoint::Type::Undefined},
    {"PE", Endpoint::Type::Input},
    {"CET", Endpoint::Type::Input},
    {"Q0", Endpoint::Type::Output},
    {"Q1", Endpoint::Type::Output},
    {"Q2", Endpoint::Type::Output},
    {"Q3", Endpoint::Type::Output},
    {"TC", Endpoint::Type::Undefined},
    {"Vcc", Endpoint::Type::Undefined}
  })
{
}

void IC74LS161::function()
{

}