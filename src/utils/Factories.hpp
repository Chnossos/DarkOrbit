/// @file   Factories.hpp
/// @author Pierre Caissial
/// @date   Created on 29/10/2021

#pragma once

// C++ includes
#include <string>

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
} // !namespace Utils
