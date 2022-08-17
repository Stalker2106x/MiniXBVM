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
        ImGui::Text("Program Counter: %s", bitsetToString(Base::Bin, computer.getRegister("ProgramCounter").read(), true).c_str());
        ImGui::Text("Memory Adress Registry: %s", bitsetToString(Base::Bin, computer.getRegister("MemoryAdressRegistry").read(), true).c_str());
        auto IR = computer.getRegister("InstructionRegister").read();
        ImGui::Text("Instruction Register: %s -> %d", bitsetToString(Base::Bin, IR, true).c_str(), bitsetToLong(IR));
        auto Acc = computer.getRegister("Accumulator").read();
        ImGui::Text("Accumulator: %s -> %d", bitsetToString(Base::Bin, Acc, true).c_str(),  bitsetToLong(Acc));
        auto BReg = computer.getRegister("BRegister").read();
        ImGui::Text("B Register: %s -> %d", bitsetToString(Base::Bin, BReg, true).c_str(),  bitsetToLong(BReg));
        ImGui::Text("Status Register: %s", computer.getFlags().c_str());
        ImGui::Text("Output Register: %s", bitsetToString(Base::Bin, computer.getRegister("Output").read(), true).c_str());
    }

    ImGui::End();
}
