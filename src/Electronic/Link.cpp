#include "Electronic/Link.hh"

Link::Link(std::initializer_list<std::shared_ptr<Endpoint>> endpoints)
: endpoints(endpoints)
{
}