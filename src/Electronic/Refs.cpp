#include "Electronic/Component.hh"

/**
 * Generic
 */

//5V Power supply
const Component PowerSupply5V = Component("PowerSupply5V", {
  {"Vcc", Endpoint::Type::Output}
}, [&] (std::vector<Endpoint> endpoints) {
  endpoints[0].link->send(5.0_V, 100.0_mA);
});

//3.3V Power supply
const Component PowerSupply3V3 = Component("PowerSupply3V3", {
  {"Vcc", Endpoint::Type::Output}
}, [&] (std::vector<Endpoint> endpoints) {
  endpoints[0].link->send(3.3_V, 100.0_mA);
});

/**
 * Clock
 */

const Component ICLM555 = Component("LM555", {
  {"GND", Endpoint::Type::Output},
  {"TR", Endpoint::Type::Input},
  {"CLK", Endpoint::Type::Output},
  {"RST", Endpoint::Type::Input},
  {"CV", Endpoint::Type::Input},
  {"THR", Endpoint::Type::Input},
  {"DIS", Endpoint::Type::Input},
  {"Vcc", Endpoint::Type::Input},
}, [&] (std::vector<Endpoint> endpoints) {

});

/**
 * Inverter
 */

const Component IC74LS04 = Component("74LS04", {
    {"1A", Endpoint::Type::Input},
    {"1Y", Endpoint::Type::Output},
    {"2A", Endpoint::Type::Input},
    {"2Y", Endpoint::Type::Output},
    {"3A", Endpoint::Type::Input},
    {"3Y", Endpoint::Type::Output},
    {"GND", Endpoint::Type::Output},
    {"Vcc", Endpoint::Type::Input},
    {"4A", Endpoint::Type::Input},
    {"4Y", Endpoint::Type::Output},
    {"5A", Endpoint::Type::Input},
    {"5Y", Endpoint::Type::Output},
    {"6A", Endpoint::Type::Input},
    {"6Y", Endpoint::Type::Output},
}, [&] (std::vector<Endpoint> endpoints) {

});

/**
 * AND Gate
 */

const Component IC74LS08 = Component("74LS08", {
    {"A1", Endpoint::Type::Input},
    {"B1", Endpoint::Type::Input},
    {"Y1", Endpoint::Type::Output},
    {"A2", Endpoint::Type::Input},
    {"B2", Endpoint::Type::Input},
    {"Y2", Endpoint::Type::Output},
    {"GND", Endpoint::Type::Output},
    {"A3", Endpoint::Type::Input},
    {"B3", Endpoint::Type::Input},
    {"Y3", Endpoint::Type::Output},
    {"A4", Endpoint::Type::Input},
    {"B4", Endpoint::Type::Input},
    {"Y4", Endpoint::Type::Output},
    {"Vcc", Endpoint::Type::Input},
}, [&] (std::vector<Endpoint> endpoints) {

});

/**
 * Counter
 */

const Component IC74LS161 = Component("74LS161", {
    {"RST", Endpoint::Type::Input},
    {"CLK", Endpoint::Type::Input},
    {"P0", Endpoint::Type::Input},
    {"P1", Endpoint::Type::Input},
    {"P2", Endpoint::Type::Input},
    {"P3", Endpoint::Type::Input},
    {"CEP", Endpoint::Type::Input},
    {"GND", Endpoint::Type::Output},
    {"PE", Endpoint::Type::Input},
    {"CET", Endpoint::Type::Input},
    {"Q0", Endpoint::Type::Output},
    {"Q1", Endpoint::Type::Output},
    {"Q2", Endpoint::Type::Output},
    {"Q3", Endpoint::Type::Output},
    {"TC", Endpoint::Type::Output},
    {"Vcc", Endpoint::Type::Input}
}, [&] (std::vector<Endpoint> endpoints) {

});