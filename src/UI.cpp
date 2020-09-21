#include "UI.hh"

#include <imgui.h>
#include <imgui/examples/imgui_impl_glut.h>
#include <imgui/examples/imgui_impl_opengl2.h>

char UI::program[1024];

void UI::draw()
{
    //Main Panel
    {
        ImGui::Begin("VM");

        ImGui::Text("8BVM READY");
        if (ImGui::Button("Run"))
        {

        }
        ImGui::SameLine();
        if (ImGui::Button("Pause"))
        {

        }
        ImGui::SameLine();
        if (ImGui::Button("Halt"))
        {

        }
        ImGui::SameLine();
        if (ImGui::Button("Reset"))
        {

        }
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        ImGui::InputTextMultiline("Program", program, IM_ARRAYSIZE(program), ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 16));
        
        ImGui::End();
    }
}
