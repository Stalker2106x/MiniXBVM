#ifndef COMPONENT_HH_
#define COMPONENT_HH_

#include <string>
#include <vector>
#include <functional>
#include <initializer_list>
#include "Electronic/Endpoint.hh"

long double operator""_V(long double x);
long double operator""_mA(long double x);

typedef std::function<void(std::vector<Endpoint>&)> ComponentFunction;

class Component
{
public:
  Component(std::string name_, std::initializer_list<Endpoint> endpoints, ComponentFunction activate);

  Endpoint &get(std::string endpointName);

private:
  std::string _name;
  std::vector<Endpoint> _endpoints;
  ComponentFunction _activate;
};

#endif /* !COMPONENT_HH_ */