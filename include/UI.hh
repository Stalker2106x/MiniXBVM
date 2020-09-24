#ifndef UI_HH_
#define UI_HH_

#include <string>
#include <imgui.h>
#include <imgui/examples/imgui_impl_glut.h>
#include <imgui/examples/imgui_impl_opengl2.h>
#include <ImGuiColorTextEdit/TextEditor.h>

#define ICON_MIN_IONIC  0xf100
#define ICON_MAX_IONIC  0xf4cd

#define ICON_NEXT       u8"\uf217"
#define ICON_PAUSE      u8"\uf341"
#define ICON_PLAY       u8"\uf488"
#define ICON_RESTART    u8"\uf38b"
#define ICON_RESET      u8"\uf2c0"

enum Font {
    Segment = 1,
    Icons
};

class UI
{
public:
    static void init();
    static void draw();
    static void vmWindow();
    static void programmerWindow();

    static ImFontAtlas* FontAtlas;

    static TextEditor asmEditor;

    static char *machineProgram;
    static char *infoModalText;
};

#endif /* !UI_HH_ */