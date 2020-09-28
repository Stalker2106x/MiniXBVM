#include "Electronic/IC.hh"
#include <algorithm>

IC::IC(std::string name, std::initializer_list<Endpoint> endpoints)
: _name(name), _endpoints(endpoints)
{
}

Endpoint &IC::get(std::string endpointName)
{
    auto endpoint = std::find_if(_endpoints.begin(), _endpoints.end(), [&](auto const &endpoint) { return (endpoint.name == endpointName); });
    if (endpoint == _endpoints.end()) throw (std::runtime_error("Endpoint is non-existant in this IC"));
    return (*endpoint);
}