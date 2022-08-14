#ifndef UI_HH_
#define UI_HH_

#include <string>
#include <imgui.h>
#include <imgui/backends/imgui_impl_glut.h>
#include <imgui/backends/imgui_impl_opengl2.h>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "UI/RamInspector.hh"
#include "UI/ComputerPanel.hh"
#include "UI/ProgrammerWindow.hh"
#include "UI/SettingsWindow.hh"
#include "UI/HelpWindow.hh"
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

    void sfmlDraw(sf::RenderWindow &window);

    ImFontAtlas* fontAtlas;
    static std::unique_ptr<UI> instance;

    ComputerPanel computerPanel;
    RamInspector ramInspector;
    ProgrammerWindow programmerWindow;
    HelpWindow helpWindow;
    SettingsWindow settingsWindow;
private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    char *infoModalText;
};

#endif /* !UI_HH_ */