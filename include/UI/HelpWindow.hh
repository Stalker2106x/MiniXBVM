#ifndef HELPWINDOW_HH_
#define HELPWINDOW_HH_

#include <SFML/Graphics.hpp>
#include "utils.hh"

class HelpWindow
{
public:
    HelpWindow();

    void update();
    void draw();
    bool _showHelp;
private:

    sf::Texture logoTexture;
    sf::Sprite logoSprite;
};

#endif /* !HELPWINDOW_HH_ */