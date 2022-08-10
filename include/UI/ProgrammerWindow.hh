#ifndef PROGRAMMERWINDOW_HH_
#define PROGRAMMERWINDOW_HH_

#include "utils.hh"
#include "Cc/Cc.hh"
#include <ImGuiColorTextEdit/TextEditor.h>

class ProgrammerWindow
{
public:
    ProgrammerWindow();

    void update();
    void draw();

private:
    TextEditor asmEditor;

    Cc::Output lastCC;
};

#endif /* !PROGRAMMERWINDOW_HH_ */