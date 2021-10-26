/// @file   main.cpp
/// @author Pierre Caissial
/// @date   Created on 14/10/2021

#include "core/Exception.hpp"
#include "engine/ScreenManager.hpp"
#include "screens/SpaceMap.hpp"

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <spdlog/spdlog.h>

static void initWindow(sf::Window & w);
static void onWindowResize(sf::RenderWindow & w, sf::Vector2f gameViewSz, sf::Vector2f windowSz);

int main() try
{
    std::locale::global(std::locale(""));

#ifndef NDEBUG
    spdlog::set_level(spdlog::level::debug);
#endif
    spdlog::set_pattern("%C-%m-%d %H:%M:%S.%e [%t] [%^%L%$] %v");

    sf::VideoMode       videoMode(820, 615, sf::VideoMode::getDesktopMode().bitsPerPixel);
    sf::ContextSettings contextSettings(videoMode.bitsPerPixel);
    constexpr auto      windowStyle = sf::Style::Default;
    sf::RenderWindow    window(videoMode, "Dark Orbit", windowStyle, contextSettings);

    initWindow(window);

    sf::RenderTexture gameTexture;
    Core::bAssert(gameTexture.create(videoMode.width, videoMode.height, contextSettings),
                  "Failed to create game texture");

    Engine::ScreenManager screenManager;
    screenManager.push<Screens::SpaceMapScreen>();

    sf::Clock clock;
    while (window.isOpen())
    {
        auto const screen = screenManager.top();

        sf::Event event; // NOLINT
        while (window.pollEvent(event))
        {
            /**/ if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::Resized)
            {
                onWindowResize(window, sf::Vector2f(videoMode.width,  videoMode.height),
                                       sf::Vector2f(event.size.width, event.size.height));
            }
            screen->onEvent(event);
        }

        screen->update(clock.restart());

        gameTexture.clear(sf::Color::White);
        screen->draw(gameTexture);
        gameTexture.display();

        window.clear();
        window.draw(sf::Sprite(gameTexture.getTexture()));
        window.display();
    }
}
catch (std::exception const & e)
{
    spdlog::critical(Core::formatExceptionStack(e));
    return EXIT_FAILURE;
}

void initWindow(sf::Window & w)
{
    spdlog::trace("Enabling Vertical Sync");
    w.setVerticalSyncEnabled(true);

    spdlog::trace("Loading Window Icon");

    sf::Image icon;
    if (!icon.loadFromFile("assets/favicon.png"))
        spdlog::warn("Failed to load window icon from 'assets/favicon.ico'");
    else
        w.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void onWindowResize(sf::RenderWindow & window, sf::Vector2f gameViewSize, sf::Vector2f windowSize)
{
    if (windowSize.x < gameViewSize.x || windowSize.y < gameViewSize.y)
    {
        window.setSize({static_cast<unsigned>(windowSize.x), static_cast<unsigned>(windowSize.y)});
        window.setView(window.getDefaultView());
    }
    else
    {
        auto const aspectRatio = gameViewSize.x / gameViewSize.y;

        float const new_width     =  aspectRatio  * windowSize.y;
        float const new_height    =  windowSize.x / aspectRatio;
        float const offset_width  = (windowSize.x - new_width ) / 2.f;
        float const offset_height = (windowSize.y - new_height) / 2.f;

        auto view = window.getDefaultView();
        if (windowSize.x >= aspectRatio * windowSize.y)
        {
            view.setViewport(sf::FloatRect(offset_width / windowSize.x, 0,
                                           new_width    / windowSize.x, 1));
        }
        else
        {
            view.setViewport(sf::FloatRect(0, offset_height / windowSize.y,
                                           1, new_height    / windowSize.y));
        }
        window.setView(view);
    }
}
