/// @file   main.cpp
/// @author Pierre Caissial
/// @date   Created on 14/10/2021

// Project includes
#include "core/Constants.hpp"
#include "core/Exception.hpp"
#include "engine/ScreenManager.hpp"
#include "screens/SpaceMap.hpp"

// Third-party includes
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <spdlog/spdlog.h>

#ifdef _WIN32
# include <windows.h>
#endif

std::string getCurrentLocale()
{
    std::string result;

#ifdef WIN32
    wchar_t name[LOCALE_NAME_MAX_LENGTH];
    if (LCIDToLocaleName(GetThreadLocale(), name, LOCALE_NAME_MAX_LENGTH, 0))
    {
        // locale names don't contain weird character so it's okay
        for (wchar_t c : std::wstring(name))
            result += (char)c;
    }
#endif

    return result;
}

static void initWindow(sf::Window & w);
static void onWindowResize(sf::RenderWindow & w, sf::Vector2u windowSz);

int main() try
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

#ifndef NDEBUG
    spdlog::set_level(spdlog::level::trace);
#endif
    spdlog::set_pattern("%C-%m-%d %H:%M:%S.%e [%t] [%^%L%$] %v");

    // Needed for localized fmt::format
    std::locale::global(std::locale(getCurrentLocale()));

    auto const       bitsDepth   = sf::VideoMode::getDesktopMode().bitsPerPixel;
    sf::VideoMode    videoMode(Constants::gameViewWidth, Constants::gameViewHeight, bitsDepth);
    constexpr auto   windowStyle = sf::Style::Default;
    sf::RenderWindow window(videoMode, Constants::windowTitle, windowStyle);

    initWindow(window);

    sf::RenderTexture gameTexture;
    Core::bAssert(gameTexture.create(videoMode.width, videoMode.height),
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
                onWindowResize(window, sf::Vector2u(event.size.width, event.size.height));

            screen->onEvent(event);
        }

        screen->update(clock.restart());

        gameTexture.clear();
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
    constexpr auto path = "assets/favicon.png";

    sf::Image icon;
    if (icon.loadFromFile(path))
        w.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    else
        spdlog::warn("Failed to load window icon from '{}'", path);
}

void onWindowResize(sf::RenderWindow & window, sf::Vector2u windowSize)
{
    if (windowSize.x < Constants::gameViewWidth || windowSize.y < Constants::gameViewHeight)
    {
        window.setSize(windowSize);
        window.setView(window.getDefaultView());
    }
    else
    {
        auto top    = 0.f;
        auto left   = 0.f;
        auto width  = 1.f;
        auto height = 1.f;

        auto const windowRatio = (float)windowSize.x / windowSize.y;
        if (windowRatio < Constants::gameViewRatio)
        {
            height = windowRatio / Constants::gameViewRatio;
            top    = (1 - height) / 2.f;
        }
        else
        {
            width = Constants::gameViewRatio / windowRatio;
            left  = (1 - width) / 2.f;
        }

        auto view = window.getDefaultView();
        view.setViewport(sf::FloatRect(left, top, width, height));
        window.setView(view);
    }
}
