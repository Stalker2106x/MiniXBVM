#include <stdexcept>
#include <math.h>
#include <string>
#include <SFML/Graphics.hpp>
#include "UI.hh"
#include "App.hh"
#include "bitset_utils.hh"
#include <imgui_internal.h>

std::unique_ptr<UI> UI::instance = nullptr;

UI::UI()
{
    infoModalText = new char[2048];
    UI::instance = std::unique_ptr<UI>(this);
}

void UI::init()
{
    backgroundTexture.loadFromFile("Data/img/background.jpg");
    backgroundSprite.setTexture(backgroundTexture);
}

void UI::menuBar()
{
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if(ImGui::MenuItem("Settings"))
            {
                settingsWindow._showSettings = true;
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help")) {
            if(ImGui::MenuItem("About"))
            {
                helpWindow._showHelp = true;
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void UI::draw()
{
    menuBar();
    settingsWindow.draw();
    computerPanel.draw();
    programmerWindow.draw();
    ramInspector.draw();
    helpWindow.draw();

    // Rendering
    ImGui::Render();
}

void UI::sfmlDraw(sf::RenderWindow &window)
{
    window.draw(backgroundSprite);
}