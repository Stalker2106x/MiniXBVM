#ifndef ENDPOINT_HH_
#define ENDPOINT_HH_

#include <string>
#include "Electronic/Link.hh"

struct Endpoint
{
public:
  enum Type {
    None,
    Input,
    Output
  };
  Endpoint(std::string name_, Type type_);

  std::shared_ptr<Link> link;
  std::string name;
  Type type;
};

#endif /* !ENDPOINT_HH_ */