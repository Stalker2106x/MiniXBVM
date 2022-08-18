#include <UI/Schematic.hh>
#include "App.hh"

Schematic::Schematic()
{
    leftArrowTexture.loadFromFile("Data/img/leftArrow.png");
    leftArrowSprite.setTexture(leftArrowTexture);
    rightArrowTexture.loadFromFile("Data/img/rightArrow.png");
    rightArrowSprite.setTexture(rightArrowTexture);
    dipSTexture.loadFromFile("Data/img/DIP_S.png");
    dipSSprite.setTexture(dipSTexture);
    dipMTexture.loadFromFile("Data/img/DIP_M.png");
    dipMSprite.setTexture(dipMTexture);
    dipETexture.loadFromFile("Data/img/DIP_E.png");
    dipESprite.setTexture(dipETexture);
}

void Schematic::update()
{
}

void Schematic::drawRegister(const std::string &regName, bool left)
{
    ImGui::Text(regName.c_str());

    const Register &reg = App::instance->computer->getRegister(regName);
    ImVec2 basePos = ImGui::GetCursorScreenPos();

    if (!left)
    {
        ImGui::Image(leftArrowSprite);
        ImGui::SameLine();
    }
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
    ImGui::Image(dipSSprite);
    ImGui::SameLine();
    ImGui::Image(dipMSprite);
    ImGui::SameLine();
    for (size_t i = 0; i <= reg.getSize(); i += 2)
    {
        ImGui::Image(dipMSprite);
        ImGui::SameLine();
    }
    ImGui::Image(dipESprite);
    ImGui::PopStyleVar();
    if (left)
    {
        ImGui::SameLine();
        ImGui::Image(rightArrowSprite);
    }

    sf::Vector2u MSize = dipMTexture.getSize();
    ImVec2 endPos = ImGui::GetCursorScreenPos();
    ImVec2 offset = ImVec2(50, (MSize.y/2) - 13);
    if (!left) offset.x += leftArrowTexture.getSize().x;
    ImGui::SetCursorScreenPos(basePos + offset);
    ImGui::Text(reg.read().to_string().c_str());
    ImGui::SetCursorScreenPos(endPos);
}

void Schematic::drawMemory(const std::string &memName)
{
    ImGui::Text(memName.c_str());

    const Memory &mem = App::instance->computer->getMemory(memName);
    ImVec2 basePos = ImGui::GetCursorScreenPos();
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
    ImGui::Image(dipSSprite);
    ImGui::SameLine();
    ImGui::Image(dipMSprite);
    ImGui::SameLine();
    for (size_t i = 0; i <= App::instance->config.ramDataBitsize; i += 2)
    {
        ImGui::Image(dipMSprite);
        ImGui::SameLine();
    }
    ImGui::Image(dipESprite);
    ImGui::PopStyleVar();
    sf::Vector2u MSize = dipMTexture.getSize();
    ImVec2 endPos = ImGui::GetCursorScreenPos();
    ImGui::SetCursorScreenPos(basePos + ImVec2(50, (MSize.y/2) - 20));
    ImGui::Button("Inspector");
    ImGui::SetCursorScreenPos(endPos);
}

void Schematic::draw()
{
    ImGui::Begin("Schematic", NULL);
    ImGui::BeginGroup();
    {
        drawRegister("ProgramCounter", true);
        drawRegister("MemoryAdressRegister", true);
        drawMemory("RAM");
        drawRegister("InstructionRegister", true);
        ImGui::EndGroup();
    }
    ImGui::SameLine();
    ImGui::BeginGroup();
    {
        ImGui::Text("W BUS");
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        ImVec2 pos = ImGui::GetCursorScreenPos();
        ImVec2 rectSize = ImVec2(200, 750);
        draw_list->AddRectFilled(pos, pos + rectSize, ImColor(0, 100, 100));
        ImGui::Dummy(rectSize);
        ImGui::EndGroup();
    }
    ImGui::SameLine();
    ImGui::BeginGroup();
    {
        drawRegister("Accumulator", false);
        drawRegister("BRegister", false);
        drawRegister("Output", false);
        ImGui::EndGroup();
    }

    ImGui::End();
}
