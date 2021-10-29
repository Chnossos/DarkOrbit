/// @file   Factories.hpp
/// @author Pierre Caissial
/// @date   Created on 29/10/2021

#pragma once

// Third-party includes
#include <spdlog/fmt/fmt.h>

namespace sf
{
    template<typename T> class Rect;
    using FloatRect = Rect<float>;

    class Font;
    class RectangleShape;
    class Text;
} // !namespace sf

namespace Utils
{
    template<class T>
    inline auto makeBoundingBox(T const & t) { return makeBoundingBox(t.getGlobalBounds()); }
    /****/ auto makeBoundingBox(sf::FloatRect const & rect) -> sf::RectangleShape;

    auto makeText(std::string const & str, sf::Font const & font) -> sf::Text;
    auto makeText(std::string const & str, sf::Font const & font,
                  unsigned int fontSize) -> sf::Text;

    template<typename... Args>
    inline auto makeText(sf::Font const & font, fmt::format_string<Args...> str, Args &&... args) {
        return makeText(fmt::format(std::move(str), std::forward<Args>(args)...), font);
    }

    template<typename... Args>
    inline auto makeText(sf::Font const & font, unsigned int fontSize,
                         fmt::format_string<Args...> str, Args &&... args) {
        return makeText(fmt::format(std::move(str), std::forward<Args>(args)...), font, fontSize);
    }
} // !namespace Utils
