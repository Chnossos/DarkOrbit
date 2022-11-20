/// @file   Factories.hpp
/// @author Pierre Caissial
/// @date   Created on 29/10/2021

#pragma once

namespace sf
{
    template<typename T> class Rect;
    using FloatRect = Rect<float>;

    class RectangleShape;
    class Text;
} // !namespace sf

namespace Utils
{
    template<class T>
    inline auto makeBoundingBox(T const & t) { return makeBoundingBox(t.getGlobalBounds()); }
    /****/ auto makeBoundingBox(sf::FloatRect const & rect) -> sf::RectangleShape;
} // !namespace Utils
