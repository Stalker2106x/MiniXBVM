#include "Electronic/Endpoint.hh"

Endpoint Endpoint::Gnd = Endpoint("Gnd", Endpoint::Type::Output);

Endpoint::Endpoint(std::string name_, Type type_ = Undefined)
: name(name_), type(type_)
{
}