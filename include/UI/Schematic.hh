#ifndef SCHEMATIC_HH_
#define SCHEMATIC_HH_

#include "graphics.hh"
#include "utils.hh"

enum ArrowPosition {
    Left,
    Right
};

enum ArrowType {
    Input,
    Output,
    Even
};

class Schematic
{
public:
    Schematic();

    void init();
    void update();

    const sf::Sprite &getArrowSprite(ArrowPosition arrowPos, ArrowType arrowType);
    const ImVec2 getChipTextOffset(ArrowPosition arrowPos, size_t contentHeight);

    void drawRegister(const std::string &regName, ArrowPosition arrowPos, ArrowType arrowType);
    void drawMemory(const std::string &memName, ArrowPosition arrowPos, ArrowType arrowType);
    void draw();

private:
    sf::Texture evenArrowTexture;
    sf::Sprite evenArrowSprite;
    sf::Texture leftArrowTexture;
    sf::Sprite leftArrowSprite;
    sf::Texture rightArrowTexture;
    sf::Sprite rightArrowSprite;
    sf::Texture dipSTexture;
    sf::Sprite dipSSprite;
    sf::Texture dipMTexture;
    sf::Sprite dipMSprite;
    sf::Texture dipETexture;
    sf::Sprite dipESprite;
};

#endif /* !SCHEMATIC_HH_ */