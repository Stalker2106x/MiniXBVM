#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>
#include <imgui_internal.h>
#include "UI/ComputerPanel.hh"
#include "App.hh"
#include "UI.hh"
#include "Computer/Computer.hh"

ComputerPanel::ComputerPanel()
{

}

void ComputerPanel::draw()
{
    Computer &computer = *(App::instance->computer);
    bool computerOn = (computer.getState() == Computer::State::Running);
    //Main Panel
    ImGui::Begin("Computer", NULL);

    if (ImGui::CollapsingHeader("Display", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::PushFont(UI::instance->fontAtlas->Fonts[Segment]);
        ImGui::Text("%s", computer.getOutput().c_str());
        ImGui::PopFont();
    }

    if (ImGui::CollapsingHeader("Computer", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::Text("Tick: %d", computer.clock.getTick());
        ImGui::Text("Frequency: %d Hz", computer.clock.getFrequency());
        int freqSlider = (int)computer.clock.getFrequency();
        if (ImGui::SliderInt("Frequency (0-300Hz)", &freqSlider, 0, 300))
        {
            computer.clock.setFrequency(freqSlider);
        }
        ImGui::Text("State: %s", (computer.clock.getState() == Clock::State::Running ? "Running" : "Paused"));
        ImGui::Text("Control: ");
        ImGui::PushFont(UI::instance->fontAtlas->Fonts[Icons]);

        if (!computerOn)
        {
            ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
        }
            //Pause/Resume
            if (ImGui::Button((computer.clock.getState() == Clock::State::Running ? ICON_PAUSE : ICON_PLAY), ImVec2(30, 30))) // Pause / Play
            {
                computer.clock.toggle();
            }
            ImGui::PopFont();
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(computer.clock.getState() == Clock::State::Running ? "Pause clock" : "Resume clock");
            ImGui::SameLine();
            ImGui::PushFont(UI::instance->fontAtlas->Fonts[Icons]);
            // Next Button
            if (ImGui::Button(ICON_NEXT, ImVec2(30, 30))) //Next
            {
                computer.clock.nextStep();
            }
            ImGui::PopFont();
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("Trigger one clock cycle");
        if (!computerOn)
        {
            ImGui::PopItemFlag();
            ImGui::PopStyleVar();
        }
        ImGui::SameLine();
        ImGui::PushFont(UI::instance->fontAtlas->Fonts[Icons]);
        if (ImGui::Button(ICON_RESTART, ImVec2(30, 30))) // Restart
        {
            computer.restart();
        }
        ImGui::PopFont();
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Restart Computer (Resets all registers)");
        ImGui::Text("Program Counter: %s", computer.dumpRegister(ProgramCounter, Base::Bin).c_str());
        ImGui::Text("Memory Adress Registry: %s", computer.dumpRegister(MemoryAdressRegistry, Base::Bin).c_str());
        ImGui::Text("Instruction Register: %s -> %s", computer.dumpRegister(InstructionRegister, Base::Bin).c_str(), computer.getInstruction().c_str());
        ImGui::Text("Accumulator: %s -> %s", computer.dumpRegister(Accumulator, Base::Bin).c_str(), computer.dumpRegister(Accumulator, Base::Dec).c_str());
        ImGui::Text("B Register: %s -> %s", computer.dumpRegister(Bregister, Base::Bin).c_str(), computer.dumpRegister(Bregister, Base::Dec).c_str());
        ImGui::Text("Status Register: %s", computer.getFlags().c_str());
        ImGui::Text("Output Register: %s", computer.dumpRegister(Output, Base::Bin).c_str());
    }

    ImGui::End();
}
