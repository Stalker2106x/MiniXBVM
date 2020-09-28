#include "Electronic/Link.hh"

Link::Link(std::initializer_list<std::shared_ptr<Endpoint>> endpoints)
: endpoints(endpoints)
{
}

void Link::send(float voltage_, float current_)
{
  voltage = voltage_;
  current = current_;
}