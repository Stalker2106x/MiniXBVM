#ifndef UI_HH_
#define UI_HH_

#include <string>
#include <imgui.h>
#include <imgui/examples/imgui_impl_glut.h>
#include <imgui/examples/imgui_impl_opengl2.h>

#define ICON_MIN_IONIC 0xf100
#define ICON_MAX_IONIC 0xf4cd

enum Font {
    Segment = 1,
    Icons
};

class UI
{
public:
    static void init();
    static void draw();

    static ImFontAtlas* FontAtlas;
    static char *asmProgram;
    static char *machineProgram;
    static char *infoModalText;
};

#endif /* !UI_HH_ */