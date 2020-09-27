#ifndef IC_HH_
#define IC_HH_

#include <string>
#include <vector>
#include <functional>
#include <initializer_list>
#include "Electronic/Endpoint.hh"

class IC
{
public:
  IC(std::string name_, std::initializer_list<Endpoint> endpoints);
  virtual void function() = 0;

private:
  std::string _name;
  std::vector<Endpoint> _endpoints;

};

#endif /* !IC_HH_ */