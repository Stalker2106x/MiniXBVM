#include "UI.hh"
#include "App.hh"
#include "Cc/Cc.hh"
#include <math.h>
#include <stdexcept>

ImFontAtlas* UI::FontAtlas = NULL;
char *UI::asmProgram = new char[2048];
char *UI::machineProgram = new char[2048];
char *UI::infoModalText = NULL;

void UI::init()
{
    std::fill(asmProgram, asmProgram + sizeof(asmProgram), 0);
    std::fill(machineProgram, machineProgram + sizeof(machineProgram), 0);
}

void UI::draw()
{
    //Main Panel
    {
        ImGui::Begin("VM", NULL);

        if (ImGui::CollapsingHeader("Clock", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Text("Tick: %d", App::clock.getTick());
            ImGui::Text("State: %s", (App::clock.getState() == Clock::State::Running ? "Running" : "Paused"));
            ImGui::Text("Control: ");
            ImGui::SameLine();
            ImGui::PushFont(FontAtlas->Fonts[Icons]);
            if (ImGui::Button(App::clock.getState() == Clock::State::Running ? u8"\uf341" : u8"\uf488")) // Pause / Play
            {
                App::clock.toggle();
            }
            ImGui::SameLine();
            if (ImGui::Button(u8"\uf217")) //Next
            {
                App::clock.nextStep();
            }
            ImGui::PopFont();
        }

        if (ImGui::CollapsingHeader("Computer", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Text("Program Counter: %s", App::computer.dumpRegister(ProgramCounter).c_str());
            ImGui::Text("Instruction Register: %s", App::computer.dumpRegister(InstructionRegister).c_str());
            ImGui::Text("Accumulator: %s", App::computer.dumpRegister(Accumulator).c_str());
            ImGui::Text("B Register: %s", App::computer.dumpRegister(Bregister).c_str());
            ImGui::Text("Output Register: %s", App::computer.dumpRegister(Output).c_str());

            ImGui::Text("Output: ");
            ImGui::SameLine();
            ImGui::PushFont(FontAtlas->Fonts[Segment]);
            ImGui::Text("88");
            ImGui::PopFont();

            //RAM
            ImGui::Text("RAM Size: %d", App::computer.getMemorySize(MemoryType::RAM));
            ImGui::Columns(2, "Bar"); // 4-ways, with border
            ImGui::Separator();
            ImGui::Text("Adress"); ImGui::NextColumn();
            ImGui::Text("Variable"); ImGui::NextColumn();
            ImGui::Separator();
            auto ramDump = App::computer.dumpMemory(MemoryType::RAM);
            for (int i = 0; i < ramDump.size(); i++)
            {
                ImGui::Text("0x%s", ramDump[i].first.c_str());    ImGui::NextColumn();
                ImGui::Text("%s", ramDump[i].second.c_str());   ImGui::NextColumn();
            }
            ImGui::Columns(1);
            ImGui::Separator();
        }

            // Using "##" to display same title but have unique identifier.
            ImGui::SetNextWindowPos(ImVec2(100, 100), ImGuiCond_FirstUseEver);
            ImGui::Begin("Programmer");

            ImGui::InputTextMultiline("ASM Program", asmProgram, IM_ARRAYSIZE(asmProgram), ImVec2(0, ImGui::GetTextLineHeight() * 25));

            ImGui::InputTextMultiline("Machine Program", machineProgram, IM_ARRAYSIZE(machineProgram), ImVec2(0, ImGui::GetTextLineHeight() * 25));

            if (ImGui::Button("Compile")) //Next
            {
                machineProgram = strdup(Cc::compile<DWORD_SIZE>(asmProgram).c_str());
            }
            ImGui::SameLine();
            if (ImGui::Button("Run")) //Next
            {
                infoModalText = strdup("Run is not implemented.");
                ImGui::OpenPopup("InfoModal");
            }
            ImGui::End();

        //Modal
        // Always center this window when appearing
        // ImVec2 center(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f);
        // ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

        // if (ImGui::BeginPopupModal("InfoModal", NULL, ImGuiWindowFlags_AlwaysAutoResize))
        // {
        //     ImGui::Text("%s", infoModalText);
        //     ImGui::Separator();

        //     ImGui::SetItemDefaultFocus();
        //     if (ImGui::Button("OK", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
        //     ImGui::EndPopup();
        // }

        // ImGui::End();
    }
}
