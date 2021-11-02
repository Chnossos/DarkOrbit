/// @file   SfmlText.hpp
/// @author Pierre Caissial
/// @date   Created on 29/10/2021

#pragma once

// Third-party includes
#include <fmt/format.h>

namespace sf
{
    class Color;
    class Font;
    class Sprite;
    class Text;
} // !namespace sf

namespace Utils
{
    auto makeText(sf::Font const & font, std::string const & str) -> sf::Text;
    auto makeText(sf::Font const & font, unsigned fontSize, std::string const & str) -> sf::Text;

    template<typename... Args>
    inline auto makeText(sf::Font const & font, fmt::format_string<Args...> str, Args &&... args) {
        return makeText(font, fmt::format(std::move(str), std::forward<Args>(args)...));
    }

    template<typename... Args>
    inline auto makeText(sf::Font const & font, unsigned fontSize,
                         fmt::format_string<Args...> str, Args &&... args) {
        return makeText(font, fontSize, fmt::format(std::move(str), std::forward<Args>(args)...));
    }

    void setOutline(sf::Text & text, sf::Color const & color, float thickness = 1.f);

    void setTextPosition (sf::Text & text, float x, float y);
    void centerIn        (sf::Text & dst, sf::Sprite const & src, float x = 0, float y = 0);
    void centerVertically(sf::Text & dst, sf::Sprite const & src, float x,     float y = 0);
} // !namespace Utils
