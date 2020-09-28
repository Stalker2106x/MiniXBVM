#ifndef LINK_HH_
#define LINK_HH_

#include <vector>
#include <memory>

class Endpoint;

struct Link
{
public:
  Link(std::initializer_list<std::shared_ptr<Endpoint>> endpoints);

  void send(float voltage_, float current_);

  float voltage; //V
  float current; //mA
  std::vector<std::shared_ptr<Endpoint>> endpoints;
};

#endif /* !LINK_HH_ */