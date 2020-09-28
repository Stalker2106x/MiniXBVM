#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "App.hh"

//Static instanciation
int App::oldTimeSinceStart;
Computer App::computer;
Clock App::clock;

int App::run(int argc, char** argv)
{   sf::RenderWindow window(sf::VideoMode(1280, 768), "Mini8BVM");
    window.setFramerateLimit(120);
    ImGui::SFML::Init(window);

    UI::init();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.Fonts->Clear();
    io.Fonts->AddFontDefault();
    io.Fonts->AddFontFromFileTTF("data/font/Segment.ttf", 32.0f);

    static const ImWchar icon_ranges[] = { ICON_MIN_IONIC, ICON_MAX_IONIC, 0 };
    io.Fonts->AddFontFromFileTTF("data/font/Ionicons.ttf", 25.0f, NULL, icon_ranges);

    ImGui::SFML::UpdateFontTexture(); // important call: updates font texture
    UI::FontAtlas = ImGui::GetIO().Fonts;


    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Time deltaTime = deltaClock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        update(deltaTime.asMilliseconds());
        ImGui::SFML::Update(window, deltaTime);

        UI::draw();

        window.clear();
        //Draw sfml stuff here
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return (0);
}

void App::update(int deltaTime)
{
    if (clock.cycle(deltaTime))
    {
        computer.cycle();
    }
}