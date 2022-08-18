#include "UI/ProgrammerWindow.hh"
#include "Editor/LanguageDef.hh"
#include "Cc/examples.h"
#include "App.hh"

ProgrammerWindow::ProgrammerWindow()
{
	asmEditor.SetLanguageDefinition(ExtTextEditor::LanguageDefinition::ASM());
	asmEditor.SetPalette(ExtTextEditor::GetCustomPalette());
}

void ProgrammerWindow::update()
{

}

void ProgrammerWindow::draw()
{
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
            ImGui::InputTextMultiline("", &lastCC.code, ImVec2(avail_size.x, avail_size.y / 2), ImGuiInputTextFlags_ReadOnly);
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    ImGui::Text("Compilation output");
    ImVec2 avail_size = ImGui::GetContentRegionAvail();
    ImGui::InputTextMultiline("##MC", &lastCC.log, ImVec2(avail_size.x, avail_size.y - 20), ImGuiInputTextFlags_ReadOnly);

    if (ImGui::Button("Compile"))
    {
        Cc compiler;
        lastCC = compiler.compile(asmEditor.GetText());
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
            App::instance->computer->getMemory("RAM").write(address, bitset(App::instance->config.ramDataBitsize, intFromString(Base::Bin, buffer)));
            ++address;
        }
        UI::instance->ramInspector.update();
    }
    if (!lastCC.success)
    {
        ImGui::PopItemFlag();
        ImGui::PopStyleVar();
    }
    ImGui::End();
}
