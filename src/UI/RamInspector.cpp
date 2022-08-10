#include <UI/RamInspector.hh>
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>
#include "App.hh"
#include "UI.hh"
#include "Computer/Computer.hh"

RamInspector::RamInspector() : _addrBase(Base::Bin), _valueBase(Base::Bin), _memorySize(0), _memoryUsedSize(0)
{
}

void RamInspector::update()
{
    Computer &computer = *(App::instance->computer);
    _memorySize = computer.getMemorySize(MemoryType::RAM);
    _memoryUsedSize = computer.getMemoryUsedSize(MemoryType::RAM);
    _ramDump = computer.dumpMemory(MemoryType::RAM, _addrBase, _valueBase);
}

void RamInspector::draw()
{
    Computer &computer = *(App::instance->computer);
    ImGui::Begin("RAM", NULL);

    ImGui::Text("Memory (%zu/%zu):", _memoryUsedSize, _memorySize);
    ImGui::SameLine();
    ImGui::ProgressBar(float(_memoryUsedSize) / float(_memorySize), ImVec2(0.0f, 0.0f));
    ImGui::SameLine();
    ImGui::PushFont(UI::instance->fontAtlas->Fonts[Icons]);
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
        auto pcValue = computer.dumpRegister(ProgramCounter, _addrBase);
        for (int i = 0; i < _ramDump.size(); i++)
        {
            bool active = (_ramDump[i].first == pcValue);
            bool empty = (i >= _memoryUsedSize);
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            if (active) ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 0, 0)));
            else if (empty) ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(47, 79, 79)));
            ImGui::Text("%s", _ramDump[i].first.c_str());
            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%s", _ramDump[i].second.c_str());
            if (active || empty) ImGui::PopStyleColor();
        }
        ImGui::EndTable();
    }

    ImGui::End();
}
