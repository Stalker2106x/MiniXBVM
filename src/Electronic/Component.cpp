#include "Electronic/Component.hh"
#include <algorithm>

//Syntaxic sugars
long double operator""_V(long double x) { return x; }
long double operator""_mA(long double x) { return x; }

Component::Component(std::string name, std::initializer_list<Endpoint> endpoints, ComponentFunction activate)
: _name(name), _endpoints(endpoints), _activate(activate)
{
}

Endpoint &Component::get(std::string endpointName)
{
    auto endpoint = std::find_if(_endpoints.begin(), _endpoints.end(), [&](auto const &endpoint) { return (endpoint.name == endpointName); });
    if (endpoint == _endpoints.end()) throw (std::runtime_error("Endpoint is non-existant in this Component"));
    return (*endpoint);
}