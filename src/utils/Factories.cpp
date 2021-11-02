/// @file   Factories.cpp
/// @author Pierre Caissial
/// @date   Created on 29/10/2021

#include "Factories.hpp"

// SFML includes
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

auto Utils::makeBoundingBox(sf::FloatRect const & rect) -> sf::RectangleShape
{
    sf::RectangleShape shape({ rect.width, rect.height });
    shape.setOutlineThickness(1.f);
    shape.setOutlineColor(sf::Color::Red);
    shape.setFillColor(sf::Color::Transparent);
    shape.setPosition(rect.left, rect.top);
    return shape;
}
