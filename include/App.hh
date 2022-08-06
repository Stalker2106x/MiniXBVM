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
  int run(int argc, char** argv);
  void update(int deltaTime);
  void draw();

  Computer computer;
  UI ui;

  static std::unique_ptr<App> instance;

private:
  int oldTimeSinceStart;
};

#endif /* !APP_HH_ */