#include "core/Exception.hpp"
#include "engine/ScreenManager.hpp"
#include "screens/SpaceMap.hpp"

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <spdlog/spdlog.h>

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
    window.setVerticalSyncEnabled(true);

    auto const aspectRatio = (float)videoMode.width / (float)videoMode.height;

    Engine::ScreenManager screenManager;
    sf::RenderTexture     gameTexture;
    sf::Clock             clock;

    Core::bAssert(gameTexture.create(videoMode.width, videoMode.height, contextSettings),
                  "Failed to create game texture");

    screenManager.push<Screens::SpaceMapScreen>();

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
                if (event.size.width < videoMode.width || event.size.height < videoMode.height)
                {
                    window.setSize({ videoMode.width, videoMode.height });
                    continue;
                }

                float const new_width     = aspectRatio * event.size.height;
                float const new_height    = event.size.width / aspectRatio;
                float const offset_width  = (event.size.width  - new_width ) / 2.f;
                float const offset_height = (event.size.height - new_height) / 2.f;

                auto view = window.getDefaultView();
                if (event.size.width >= aspectRatio * event.size.height)
                {
                    view.setViewport(sf::FloatRect(offset_width / event.size.width, 0,
                                                   new_width    / event.size.width, 1));
                }
                else
                {
                    view.setViewport(sf::FloatRect(0, offset_height / event.size.height,
                                                   1, new_height    / event.size.height));
                }
                window.setView(view);
            }
            else
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
