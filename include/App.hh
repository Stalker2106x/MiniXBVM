#ifndef APP_HH_
#define APP_HH_

#include <imgui.h>
#include <imgui-SFML.h>

#include "UI.hh"
#include "Computer/Computer.hh"
#include "Clock.hh"

class App
{
public:
    static int run(int argc, char** argv);
    static void update(int deltaTime);
    static void draw();

  static Computer computer;
  static Clock clock;

private:
  static int oldTimeSinceStart;
};

#endif /* !APP_HH_ */