#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>
#include <imgui-SFML.h>
#include "UI/HelpWindow.hh"

HelpWindow::HelpWindow()
{
    logoTexture.loadFromFile("Data/img/logo.png");
    logoSprite.setTexture(logoTexture);

    _showHelp = false;
}

void HelpWindow::update()
{

}

void HelpWindow::draw()
{
    if (!_showHelp) return;
    ImGui::Begin("Help", NULL);

    ImGui::Image(logoSprite);
    ImGui::Text("Welcome to Mini8BVM, the 8-Bit CPU Emulator Written in C++");
    if (ImGui::Button("Dismiss"))
    {
        _showHelp = false;
    }

    ImGui::End();
}