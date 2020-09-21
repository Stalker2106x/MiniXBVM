#ifndef APP_HH_
#define APP_HH_

#include <imgui.h>
#include <imgui/examples/imgui_impl_glut.h>
#include <imgui/examples/imgui_impl_opengl2.h>
#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/freeglut.h>
#endif

#ifdef _MSC_VER
#pragma warning (disable: 4505) // unreferenced local function has been removed
#endif

#include "UI.hh"
#include "Computer.hh"
#include "Clock.hh"

class App
{
public:
    static int run(int argc, char** argv);
    static void mainLoop();
    static void update(int deltaTime);
    static void draw();

private:
  static int oldTimeSinceStart;
  static Computer cpu;
  static Clock clock;

};

#endif /* !APP_HH_ */