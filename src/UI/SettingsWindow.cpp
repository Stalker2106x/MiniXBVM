#include "UI/SettingsWindow.hh"
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>
#include "App.hh"

SettingsWindow::SettingsWindow()
{
    _showSettings = false;
}

void SettingsWindow::update()
{
    ramAddrSize = std::to_string(App::instance->config.ramAddrBitsize);
    ramDataSize = std::to_string(App::instance->config.ramDataBitsize);
}

void SettingsWindow::draw()
{
    if (!_showSettings) return;
    ImGui::Begin("Settings", NULL);

    ImGui::InputText("RAM Address size (in bits)", &ramAddrSize);
    ImGui::InputText("RAM Data size (in bits)", &ramDataSize);
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("Apply configuration (Will completely reset computer)");
    if (ImGui::Button("Apply"))
    {
        App::instance->config.ramAddrBitsize = atoi(ramAddrSize.c_str());
        App::instance->config.ramDataBitsize = atoi(ramDataSize.c_str());
        App::instance->setComputer();
        UI::instance->ramInspector.update();
        _showSettings = false;
    }
    ImGui::SameLine();
    if (ImGui::Button("Cancel"))
    {
        _showSettings = false;
    }
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("Closes this window without altering computer");

    ImGui::End();
}