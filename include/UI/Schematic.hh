#ifndef SCHEMATIC_HH_
#define SCHEMATIC_HH_

#include "graphics.hh"
#include "utils.hh"

class Schematic
{
public:
    Schematic();

    void update();

    void drawRegister(const std::string &regName, bool left);
    void drawMemory(const std::string &memName);
    void draw();

private:
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