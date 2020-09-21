#ifndef UI_HH_
#define UI_HH_

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

class UI
{
public:
    UI(int argc, char** argv);
};

#endif /* !UI_HH_ */