#include <SFML/Window/Window.hpp>
#include <spdlog/spdlog.h>
#include <iostream>

int main()
{
    auto const currentMode = sf::VideoMode::getDesktopMode();
    spdlog::info("Mode: {:>4}x{:<4} (depth: {}) [current]",
                 currentMode.width, currentMode.height, currentMode.bitsPerPixel);

    auto const modes = sf::VideoMode::getFullscreenModes();
    for (auto const & mode : modes)
        spdlog::info("Mode: {:>4}x{:<4} (depth: {})", mode.width, mode.height, mode.bitsPerPixel);

    sf::Window window({ 1280, 720, currentMode.bitsPerPixel }, "Dark Orbit");

    std::cin.get();
}
