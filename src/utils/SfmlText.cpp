/// @file   SfmlText.cpp
/// @author Pierre Caissial
/// @date   Created on 29/10/2021

#include "SfmlText.hpp"

// Project includes
#include "../core/Constants.hpp"

// third-party includes
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

auto Utils::makeText(sf::Font const & font, std::string const & str) -> sf::Text
{
    return makeText(font, Constants::fontSize, str);
}

auto Utils::makeText(sf::Font const & font, unsigned fontSize, std::string const & str) -> sf::Text
{
    sf::Text text(str, font, fontSize);
    return text;
}

void Utils::setTextPosition(sf::Text & text, float x, float y)
{
    text.setPosition(std::ceilf(x - text.getLocalBounds().left),
                     std::ceilf(y - text.getLocalBounds().top));
}

void Utils::setOutline(sf::Text & text, sf::Color const & color, float thickness)
{
    text.setOutlineThickness(thickness);
    text.setOutlineColor(color);
}

void Utils::centerIn(sf::Text & dst, sf::Sprite const & src, float x, float y)
{
    float const width  = src.getGlobalBounds().width  / 2 - dst.getGlobalBounds().width  / 2;
    float const height = src.getGlobalBounds().height / 2 - dst.getGlobalBounds().height / 2;

    dst.setPosition(
        std::ceilf(src.getGlobalBounds().left + width  - dst.getLocalBounds().left + x),
        std::ceilf(src.getGlobalBounds().top  + height - dst.getLocalBounds().top  + y)
    );
}

void Utils::centerVertically(sf::Text & dst, sf::Sprite const & src, float x, float y)
{
    float const height = src.getGlobalBounds().height / 2 - dst.getGlobalBounds().height / 2;
    dst.setPosition(std::ceilf(x),
                    std::ceilf(src.getGlobalBounds().top + height - dst.getLocalBounds().top + y));
}
