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
#include <spdlog/async.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#ifdef _WIN32
# include <windows.h>
#endif

namespace
{
    void configureLogging();
    void initWindow(sf::Window & w);
    void onWindowResize(sf::RenderWindow & w, sf::Vector2u windowSz);
    std::string getCurrentLocale();
} // !namespace

int main() try
{
    configureLogging();

    sf::RenderWindow window;
    initWindow(window);

    sf::RenderTexture gameTexture;
    Core::bAssert(gameTexture.create(window.getSize().x, window.getSize().y),
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
    SPDLOG_CRITICAL(Core::formatExceptionStack(e));
    return EXIT_FAILURE;
}

namespace
{
    void configureLogging()
    {
        spdlog::set_level(spdlog::level::trace);
#ifdef NDEBUG
        spdlog::set_pattern("%C-%m-%d %H:%M:%S.%e [%t] [%^%L%$] %v (%s:%#)");
#else
        spdlog::set_pattern("%C-%m-%d %H:%M:%S.%e [%t] [%^%L%$] %v (%s:%!:%#)");
#endif

#ifdef _WIN32
        // Enable logs when started from a terminal (IDE or external)
        if (AttachConsole(ATTACH_PARENT_PROCESS))
            SetConsoleOutputCP(CP_UTF8);
#endif

        auto console = spdlog::create_async_nb<spdlog::sinks::stdout_color_sink_mt>("console");
        spdlog::set_default_logger(std::move(console));

        // Needed for localized string format
        std::locale const currentLocale(getCurrentLocale());
        std::locale::global(currentLocale);
        SPDLOG_TRACE("Current locale: {}", currentLocale.c_str());
    }

    void initWindow(sf::Window & w)
    {
        auto const bitsDepth = sf::VideoMode::getDesktopMode().bitsPerPixel;
        w.create(sf::VideoMode(Constants::gameViewWidth, Constants::gameViewHeight, bitsDepth),
                 Constants::windowTitle, sf::Style::Default);

        SPDLOG_DEBUG("Enabling vertical sync");
        w.setVerticalSyncEnabled(true);

        SPDLOG_TRACE("Loading application icon");
        constexpr auto path = "assets/favicon.png";

        if (sf::Image icon; icon.loadFromFile(path))
            w.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
        else
            spdlog::warn("Failed to load application icon from '{}'", path);
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

    std::string getCurrentLocale()
    {
        std::string result;
#ifdef _WIN32
        wchar_t name[LOCALE_NAME_MAX_LENGTH];
        if (auto size = LCIDToLocaleName(GetThreadLocale(), name, LOCALE_NAME_MAX_LENGTH, 0))
        {
            result.resize(static_cast<std::size_t>(--size)); // Decrement to remove leading '\0'
            // locale names don't contain weird character so it's okay
            std::transform(name, name + size, result.begin(), [](auto const c) { return (char)c; });
        }
#endif
        return result;
    }
} // !namespace
