#ifndef ENDPOINT_HH_
#define ENDPOINT_HH_

#include <string>
#include "Electronic/Link.hh"

struct Endpoint
{
public:
  enum Type {
    Undefined,
    Input,
    Output
  };
  Endpoint(std::string name_, Type type_);

  static Endpoint Gnd; //Ground point

  std::shared_ptr<Link> link;
  std::string name;
  Type type;
};

#endif /* !ENDPOINT_HH_ */