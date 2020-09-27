#include "Electronic/IC.hh"

IC::IC(std::string name, std::initializer_list<Endpoint> endpoints)
: _name(name), _endpoints(endpoints)
{
}