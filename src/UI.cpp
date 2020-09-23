#include <stdexcept>
#include <math.h>
#include "UI.hh"
#include "App.hh"
#include "Cc/Cc.hh"
#include "bitset_utils.hh"
#include "Cc/examples.h"

ImFontAtlas* UI::FontAtlas = NULL;
char *UI::asmProgram = new char[2048];
char *UI::machineProgram = new char[2048];
char *UI::infoModalText = new char[2048];

void UI::init()
{
    memset(asmProgram, 0, 2047);
    asmProgram[2047] = '\0';
    memset(machineProgram, 0, 2047);
    machineProgram[2047] = '\0';
}

void UI::draw()
{
    //Main Panel
    ImGui::Begin("VM", NULL);

    if (ImGui::CollapsingHeader("Display", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::Text("Output: ");
        ImGui::SameLine();
        ImGui::PushFont(FontAtlas->Fonts[Segment]);
        ImGui::Text("%s", App::computer.getOutput().c_str());
        ImGui::PopFont();
    }

    if (ImGui::CollapsingHeader("Clock", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::Text("Tick: %d", App::clock.getTick());
        ImGui::Text("Frequency: %d Hz", App::clock.getFrequency());
        int freqSlider = (int)App::clock.getFrequency();
        if (ImGui::SliderInt("Frequency (0-300Hz)", &freqSlider, 0, 300))
        {
            App::clock.setFrequency(freqSlider);
        }
        ImGui::Text("State: %s", (App::clock.getState() == Clock::State::Running ? "Running" : "Paused"));
        ImGui::Text("Control: ");
        ImGui::PushFont(FontAtlas->Fonts[Icons]);
        if (ImGui::Button((App::clock.getState() == Clock::State::Running ? ICON_PAUSE : ICON_PLAY), ImVec2(30, 30))) // Pause / Play
        {
            App::clock.toggle();
        }
        ImGui::PopFont();
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip(App::clock.getState() == Clock::State::Running ? "Pause clock" : "Resume clock");
        ImGui::SameLine();
        ImGui::PushFont(FontAtlas->Fonts[Icons]);
        // Next Button
        if (ImGui::Button(ICON_NEXT, ImVec2(30, 30))) //Next
        {
            App::clock.nextStep();
        }
        ImGui::PopFont();
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Trigger one clock cycle");
    }

    if (ImGui::CollapsingHeader("Computer", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::PushFont(FontAtlas->Fonts[Icons]);
        if (ImGui::Button(ICON_RESTART, ImVec2(30, 30))) // Restart
        {
            App::computer.restart();
        }
        ImGui::PopFont();
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Restart Computer (Reset all registers)");
        ImGui::SameLine();
        ImGui::PushFont(FontAtlas->Fonts[Icons]);
        if (ImGui::Button(ICON_RESET, ImVec2(30, 30))) // Reset
        {
            App::computer.reset();
        }
        ImGui::PopFont();
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Reset Computer (Reset everything)");
        ImGui::Text("State: %s", (App::computer.getState() == Computer::State::Running ? "Running" : "Off"));
        ImGui::Text("Program Counter: %s", App::computer.dumpRegister(ProgramCounter).c_str());
        ImGui::Text("Memory Adress Registry: %s", App::computer.dumpRegister(MemoryAdressRegistry).c_str());
        ImGui::Text("Instruction Register: %s", App::computer.dumpRegister(InstructionRegister).c_str());
        ImGui::Text("Instruction: %s", App::computer.getInstruction().c_str());
        ImGui::Text("Accumulator: %s", App::computer.dumpRegister(Accumulator).c_str());
        ImGui::Text("B Register: %s", App::computer.dumpRegister(Bregister).c_str());
        ImGui::Text("Output Register: %s", App::computer.dumpRegister(Output).c_str());

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

    programmerWindow();

    ImGui::End();
}

void UI::programmerWindow()
{
    ImGui::Begin("Programmer", NULL,  ImGuiWindowFlags_MenuBar);

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Examples Programs"))
        {
            if (ImGui::MenuItem("Addition"))
            {
                std::string code = EXAMPLE_ADD;
                strncpy(asmProgram, code.c_str(), code.length()-1);
            }
            if (ImGui::MenuItem("Substraction"))
            {
                std::string code = EXAMPLE_SUB;
                strncpy(asmProgram, code.c_str(), code.length()-1);
            }
            if (ImGui::MenuItem("Multiplication"))
            {
                std::string code = EXAMPLE_MUL;
                strncpy(asmProgram, code.c_str(), code.length()-1);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    ImGui::Text("ASM Program");
    ImGui::InputTextMultiline("ASM", asmProgram, 2047, ImVec2(ImGui::GetContentRegionAvailWidth(), ImGui::GetTextLineHeight() * 20));
    ImGui::Text("Machine Program");
    ImGui::InputTextMultiline("MC", machineProgram, 2047, ImVec2(ImGui::GetContentRegionAvailWidth(), ImGui::GetTextLineHeight() * 20), ImGuiInputTextFlags_ReadOnly);

    if (ImGui::Button("Compile"))
    {
        try {
            memset(machineProgram, 0, 2047);
            std::string code = Cc::compile<WORD_SIZE>(asmProgram);
            strncpy(machineProgram, code.c_str(), code.length()-1);
        } catch(std::runtime_error e) {
            strncpy(machineProgram, e.what(), strlen(e.what()-1));
        }
    }
    ImGui::SameLine();
    if (ImGui::Button("Load to RAM"))
    {
        std::istringstream ss(machineProgram);
        std::string buffer;
        std::bitset<WORD_SIZE> address = std::bitset<WORD_SIZE>(0);

        while(std::getline(ss, buffer, '\n'))
        {
            App::computer.writeMemory(MemoryType::RAM, address, std::bitset<DWORD_SIZE>(buffer));
            ++address;
        }
    }
    ImGui::End();
}
