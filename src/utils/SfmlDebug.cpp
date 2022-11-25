/// @file   SfmlDebug.cpp
/// @author Pierre Caissial
/// @date   Created on 29/10/2021

#include "SfmlDebug.hpp"

// third-party includes
#include <SFML/Graphics/Rect.hpp>
#include <fmt/format.h>

// C++ includes
#include <ostream>

std::ostream & sf::operator<<(std::ostream & os, FloatRect const & rect)
{
    return os << fmt::format("FloatRect(left: {}, top: {}, width: {}, height: {})",
                             rect.left, rect.top, rect.width, rect.height);
}

std::ostream & sf::operator<<(std::ostream & os, Vector2f const & vec)
{
    return os << fmt::format("Vector2f({}, {})", vec.x, vec.y);
}
