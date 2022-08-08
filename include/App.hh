#ifndef APP_HH_
#define APP_HH_

#include <imgui.h>
#include <imgui-SFML.h>

#include "UI.hh"
#include "Cc/Cc.hh"
#include "Computer/Computer.hh"

class App
{
public:
  App();
  
  void setComputer();
  int run(int argc, char** argv);
  void update(int deltaTime);
  void draw();

  std::unique_ptr<Computer> computer;
  UI ui;
  Config config;

  static std::unique_ptr<App> instance;

private:
  int oldTimeSinceStart;
};

#endif /* !APP_HH_ */