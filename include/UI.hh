#ifndef UI_HH_
#define UI_HH_

#include <string>
#include <imgui.h>
#include <imgui/backends/imgui_impl_glut.h>
#include <imgui/backends/imgui_impl_opengl2.h>
#include <ImGuiColorTextEdit/TextEditor.h>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "utils.hh"

#define ICON_MIN_IONIC  0xf100
#define ICON_MAX_IONIC  0xf4cd

#define ICON_NEXT       u8"\uf217"
#define ICON_STEP       u8"\uf365"
#define ICON_PAUSE      u8"\uf341"
#define ICON_PLAY       u8"\uf488"
#define ICON_RESTART    u8"\uf36d"
#define ICON_RESET      u8"\uf366"
#define ICON_POWER      u8"\uf359"
#define ICON_ERASE      u8"\uf4c5"

enum Font {
    Segment = 1,
    Icons
};

class UI
{
public:
    UI();
    void init();
    void draw();
    void menuBar();
    void vmWindow();
    void ramInspector();
    void programmerWindow();
    void help();
    
    void sfmlDraw(sf::RenderWindow &window);

    ImFontAtlas* fontAtlas;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Texture logoTexture;
    sf::Sprite logoSprite;

    TextEditor asmEditor;

    bool validMachineProgram;
    char *machineProgram;
    char *infoModalText;

    static std::unique_ptr<UI> instance;
private:
    bool _showHelp;
    Base _addrBase;
    Base _valueBase;
};

#endif /* !UI_HH_ */