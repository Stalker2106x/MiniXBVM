#include <UI/Schematic.hh>
#include "App.hh"

Schematic::Schematic()
{
}

void Schematic::init()
{
    const sf::Vector2f scale = sf::Vector2f(App::instance->config.UIScale / 2, App::instance->config.UIScale / 2);
    evenArrowTexture.loadFromFile("Data/img/evenArrow.png");
    evenArrowSprite.setTexture(evenArrowTexture);
    evenArrowSprite.setScale(scale);
    leftArrowTexture.loadFromFile("Data/img/leftArrow.png");
    leftArrowSprite.setTexture(leftArrowTexture);
    leftArrowSprite.setScale(scale);
    rightArrowTexture.loadFromFile("Data/img/rightArrow.png");
    rightArrowSprite.setTexture(rightArrowTexture);
    rightArrowSprite.setScale(scale);
    dipSTexture.loadFromFile("Data/img/DIP_S.png");
    dipSSprite.setTexture(dipSTexture);
    dipSSprite.setScale(scale);
    dipMTexture.loadFromFile("Data/img/DIP_M.png");
    dipMSprite.setTexture(dipMTexture);
    dipMSprite.setScale(scale);
    dipETexture.loadFromFile("Data/img/DIP_E.png");
    dipESprite.setTexture(dipETexture);
    dipESprite.setScale(scale);
}

void Schematic::update()
{
}

const sf::Sprite &Schematic::getArrowSprite(ArrowPosition arrowPos, ArrowType arrowType)
{
    if (arrowPos == ArrowPosition::Left)
    {
        if (arrowType == ArrowType::Input) return (rightArrowSprite);
        else if (arrowType == ArrowType::Output) return (leftArrowSprite);
        else return (evenArrowSprite);
    }
    else
    {
        if (arrowType == ArrowType::Input) return (leftArrowSprite);
        else if (arrowType == ArrowType::Output) return (rightArrowSprite);
        else return (evenArrowSprite);
    }
}

const ImVec2 Schematic::getChipTextOffset(ArrowPosition arrowPos, size_t contentHeight)
{
    size_t xOffset = dipSTexture.getSize().x * dipSSprite.getScale().x;
    size_t yOffset = dipMTexture.getSize().y * dipMSprite.getScale().y;
    ImVec2 offset = ImVec2(xOffset, (yOffset/2) - (contentHeight/2));
    if (arrowPos == ArrowPosition::Left) offset.x += leftArrowTexture.getSize().x * leftArrowSprite.getScale().x;
    return (offset);
}

void Schematic::drawRegister(const std::string &regName, ArrowPosition arrowPos, ArrowType arrowType)
{
    ImGui::Text(regName.c_str());

    const Register &reg = App::instance->computer->getRegister(regName);
    ImVec2 basePos = ImGui::GetCursorScreenPos();

    if (arrowPos == ArrowPosition::Left)
    {
        ImGui::Image(getArrowSprite(arrowPos, arrowType));
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
    if (arrowPos == ArrowPosition::Right)
    {
        ImGui::SameLine();
        ImGui::Image(getArrowSprite(arrowPos, arrowType));
    }

    ImVec2 endPos = ImGui::GetCursorScreenPos();
    ImGui::SetCursorScreenPos(basePos + getChipTextOffset(arrowPos, DEFAULT_FONT_SIZE));
    ImGui::Text(reg.read().to_string().c_str());
    ImGui::SetCursorScreenPos(endPos);
}

void Schematic::drawMemory(const std::string &memName, ArrowPosition arrowPos, ArrowType arrowType)
{
    ImGui::Text(memName.c_str());

    const Memory &mem = App::instance->computer->getMemory(memName);
    ImVec2 basePos = ImGui::GetCursorScreenPos();

    if (arrowPos == ArrowPosition::Left)
    {
        ImGui::Image(getArrowSprite(arrowPos, arrowType));
        ImGui::SameLine();
    }
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
    if (arrowPos == ArrowPosition::Right)
    {
        ImGui::SameLine();
        ImGui::Image(getArrowSprite(arrowPos, arrowType));
    }

    ImVec2 endPos = ImGui::GetCursorScreenPos();
    ImGui::SetCursorScreenPos(basePos + getChipTextOffset(arrowPos, 20));
    ImGui::Button("Inspect");
    ImGui::SetCursorScreenPos(endPos);
}

void Schematic::draw()
{
    ImGui::Begin("Schematic", NULL);
    ImGui::BeginGroup();
    {
        drawRegister("ProgramCounter", ArrowPosition::Right, ArrowType::Output);
        drawRegister("MemoryAdressRegister", ArrowPosition::Right, ArrowType::Input);
        drawMemory("RAM", ArrowPosition::Right, ArrowType::Output);
        drawRegister("InstructionRegister", ArrowPosition::Right, ArrowType::Even);
        ImGui::EndGroup();
    }
    ImGui::SameLine();
    ImGui::BeginGroup();
    {
        ImGui::Text("W BUS");
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        ImVec2 pos = ImGui::GetCursorScreenPos();
        ImVec2 rectSize = ImVec2(100, 300);
        draw_list->AddRectFilled(pos, pos + rectSize, ImColor(0, 100, 100));
        ImGui::Dummy(rectSize);
        ImGui::EndGroup();
    }
    ImGui::SameLine();
    ImGui::BeginGroup();
    {
        drawRegister("Accumulator", ArrowPosition::Left, ArrowType::Even);
        drawRegister("BRegister", ArrowPosition::Left, ArrowType::Input);
        drawRegister("Output", ArrowPosition::Left, ArrowType::Input);
        ImGui::EndGroup();
    }

    ImGui::End();
}
