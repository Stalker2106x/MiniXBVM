#include <stdexcept>
#include <math.h>
#include <string>
#include <SFML/Graphics.hpp>
#include "UI.hh"
#include "App.hh"
#include "Cc/Cc.hh"
#include "bitset_utils.hh"
#include "Cc/examples.h"
#include "Editor/LanguageDef.hh"
#include <imgui_internal.h>

std::unique_ptr<UI> UI::instance = nullptr;

UI::UI()
{
    ramAddrSize = new char[128];
    ramDataSize = new char[128];
    compilationOutput = new char[2048];
    compilationLogs = new char[2048];
    infoModalText = new char[2048];
    UI::instance = std::unique_ptr<UI>(this);
}

void UI::init()
{
    memset(compilationOutput, 0, 2047);
    compilationOutput[2047] = '\0';
    memset(compilationLogs, 0, 2047);
    compilationLogs[2047] = '\0';

    sprintf(ramAddrSize, "%d", App::instance->config.ramAddrBitsize);
    sprintf(ramDataSize, "%d", App::instance->config.ramDataBitsize);

	asmEditor.SetLanguageDefinition(ExtTextEditor::LanguageDefinition::ASM());
	asmEditor.SetPalette(ExtTextEditor::GetCustomPalette());

    backgroundTexture.loadFromFile("Data/img/background.jpg");
    backgroundSprite.setTexture(backgroundTexture);

    logoTexture.loadFromFile("Data/img/logo.png");
    logoSprite.setTexture(logoTexture);

    _showHelp = false;
    _showSettings = false;
    _addrBase = Base::Bin;
    _valueBase = Base::Bin;
}

void UI::menuBar()
{
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if(ImGui::MenuItem("Settings"))
            {
                _showSettings = true;
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help")) {
            if(ImGui::MenuItem("About"))
            {
                _showHelp = true;
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void UI::draw()
{
    menuBar();
    settingsWindow();
    vmWindow();
    programmerWindow();
    ramInspector();
    helpWindow();

    // Rendering
    ImGui::Render();
}

void UI::vmWindow()
{
    Computer &computer = *(App::instance->computer);
    bool computerOn = (computer.getState() == Computer::State::Running);
    //Main Panel
    ImGui::Begin("VM", NULL);

    if (ImGui::CollapsingHeader("Display", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::PushFont(fontAtlas->Fonts[Segment]);
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
        ImGui::PushFont(fontAtlas->Fonts[Icons]);

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
            ImGui::PushFont(fontAtlas->Fonts[Icons]);
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
        ImGui::PushFont(fontAtlas->Fonts[Icons]);
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

void UI::ramInspector()
{
    Computer &computer = *(App::instance->computer);
    ImGui::Begin("RAM", NULL);

    ImGui::Text("Memory (%d/%d):", computer.getMemoryUsedSize(MemoryType::RAM), computer.getMemorySize(MemoryType::RAM));
    ImGui::SameLine();
    ImGui::ProgressBar(float(computer.getMemoryUsedSize(MemoryType::RAM)) / float(computer.getMemorySize(MemoryType::RAM)), ImVec2(0.0f, 0.0f));
    ImGui::SameLine();
    ImGui::PushFont(fontAtlas->Fonts[Icons]);
    if (ImGui::Button(ICON_ERASE, ImVec2(30, 30))) // Restart
    {
        computer.reset();
    }
    ImGui::PopFont();
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("Empty RAM (Restarts computer)");
    //Array
    const int COLUMNS_COUNT = 2;
    if (ImGui::BeginTable("RAM", COLUMNS_COUNT, ImGuiTableFlags_Borders))
    {
        ImGui::TableSetupColumn("Adress");
        ImGui::TableSetupColumn("Data");

        // Instead of calling TableHeadersRow() we'll submit custom headers ourselves
        ImGui::TableNextRow(ImGuiTableRowFlags_Headers);
        for (int column = 0; column < COLUMNS_COUNT; column++)
        {
            ImGui::TableSetColumnIndex(column);
            const char* column_name = ImGui::TableGetColumnName(column); // Retrieve name passed to TableSetupColumn()
            ImGui::PushID(column);
            ImGui::TableHeader(column_name);
            ImGui::SameLine(ImGui::GetColumnWidth()-20);
            if (ImGui::Button(baseToLabel(column == 0 ? _addrBase : _valueBase).c_str(), ImVec2(30, 20)))
            {
                if (column == 0)
                {
                    if (_addrBase == Base::Bin) _addrBase = Base::Oct;
                    else if (_addrBase == Base::Oct) _addrBase = Base::Hex;
                    else if (_addrBase == Base::Hex) _addrBase = Base::Dec;
                    else if (_addrBase == Base::Dec) _addrBase = Base::Bin;
                }
                else if (column == 1)
                {
                    if (_valueBase == Base::Bin) _valueBase = Base::Oct;
                    else if (_valueBase == Base::Oct) _valueBase = Base::Hex;
                    else if (_valueBase == Base::Hex) _valueBase = Base::Dec;
                    else if (_valueBase == Base::Dec) _valueBase = Base::ASCII;
                    else if (_valueBase == Base::ASCII) _valueBase = Base::Bin;
                }
            }
            ImGui::PopID();
        }
        auto ramDump = computer.dumpMemory(MemoryType::RAM, _addrBase, _valueBase);
        auto pcValue = computer.dumpRegister(ProgramCounter, _addrBase);
        for (int i = 0; i < ramDump.size(); i++)
        {
            bool active = (ramDump[i].first == pcValue);
            bool empty = (ramDump[i].second == bitsetToString(Base::Bin, bitset(App::instance->config.ramDataBitsize, 0)));
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            if (active) ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 0, 0)));
            if (empty) ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(47, 79, 79)));
            ImGui::Text("%s", ramDump[i].first.c_str());
            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%s", ramDump[i].second.c_str());
            if (active || empty) ImGui::PopStyleColor();
        }
        ImGui::EndTable();
    }

    ImGui::End();
}

void UI::programmerWindow()
{
    static Cc::Output lastCC;
    ImGui::Begin("Programmer", NULL,  ImGuiWindowFlags_MenuBar);

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Examples Programs"))
        {
            if (ImGui::MenuItem("Addition"))
            {
                asmEditor.SetText(EXAMPLE_ADD);
            }
            if (ImGui::MenuItem("Substraction"))
            {
                asmEditor.SetText(EXAMPLE_SUB);
            }
            if (ImGui::MenuItem("Multiplication"))
            {
                asmEditor.SetText(EXAMPLE_MUL);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
    if (ImGui::BeginTabBar("EditorTabs", ImGuiTabBarFlags_None))
    {
        if (ImGui::BeginTabItem("Assembly"))
        {
            ImGui::Text("ASM Program");
            ImVec2 avail_size = ImGui::GetContentRegionAvail();
            asmEditor.Render("TextEditor", ImVec2(avail_size.x, avail_size.y / 2));
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Generated"))
        {
            ImGui::Text("Generated machine code");
            ImVec2 avail_size = ImGui::GetContentRegionAvail();
            ImGui::InputTextMultiline("", compilationOutput, 2047, ImVec2(avail_size.x, avail_size.y / 2), ImGuiInputTextFlags_ReadOnly);
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    ImGui::Text("Compilation output");
    ImVec2 avail_size = ImGui::GetContentRegionAvail();
    ImGui::InputTextMultiline("##MC", compilationLogs, 2047, ImVec2(avail_size.x, avail_size.y - 20), ImGuiInputTextFlags_ReadOnly);

    if (ImGui::Button("Compile"))
    {
        memset(compilationLogs, 0, 2047);
        memset(compilationOutput, 0, 2047);
        Cc compiler;
        lastCC = compiler.compile(asmEditor.GetText());
        if (lastCC.code.length() > 0 && lastCC.log.length() > 0)
        {
            strncpy(compilationLogs, lastCC.log.c_str(), lastCC.log.length()-1);
            strncpy(compilationOutput, lastCC.code.c_str(), lastCC.code.length()-1);
        }
    }
    ImGui::SameLine();
    if (!lastCC.success)
    {
        ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
    }
    if (ImGui::Button("Load to RAM"))
    {
        std::istringstream ss(lastCC.code);
        std::string buffer;
        bitset address = bitset(App::instance->config.ramAddrBitsize, 0);

        while(std::getline(ss, buffer, '\n'))
        {
            App::instance->computer->writeMemory(MemoryType::RAM, address, bitset(App::instance->config.ramDataBitsize, intFromString(Base::Bin, buffer)));
            ++address;
        }
    }
    if (!lastCC.success)
    {
        ImGui::PopItemFlag();
        ImGui::PopStyleVar();
    }
    ImGui::End();
}

void UI::settingsWindow()
{
    if (!_showSettings) return;
    ImGui::Begin("Settings", NULL);

    ImGui::InputText("RAM Address size (in bits)", ramAddrSize, IM_ARRAYSIZE(ramAddrSize));
    ImGui::InputText("RAM Data size (in bits)", ramDataSize, IM_ARRAYSIZE(ramDataSize));
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("Apply configuration (Will completely reset computer)");
    if (ImGui::Button("Apply"))
    {
        App::instance->config.ramAddrBitsize = atoi(ramAddrSize);
        App::instance->config.ramDataBitsize = atoi(ramDataSize);
        App::instance->setComputer();
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

void UI::helpWindow()
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

void UI::sfmlDraw(sf::RenderWindow &window)
{
    window.draw(backgroundSprite);
}