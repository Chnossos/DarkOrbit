/// @file   SfmlDebug.cpp
/// @author Pierre Caissial
/// @date   Created on 29/10/2021

#include "SfmlDebug.hpp"

// SFML includes
#include <SFML/Graphics/Rect.hpp>

// Third-party includes
#include <fmt/format.h>

// C++ includes
#include <ostream>

std::ostream & sf::operator<<(std::ostream & os, FloatRect const & rect)
{
    return os << fmt::format("left = {} ; top = {} ; width = {} ; height = {}",
                             rect.left, rect.top, rect.width, rect.height);
}
