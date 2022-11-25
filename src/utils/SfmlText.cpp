/// @file   SfmlText.cpp
/// @author Pierre Caissial
/// @date   Created on 29/10/2021

#include "SfmlText.hpp"

// Project includes
#include "../core/Constants.hpp"

// third-party includes
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

auto Text::make(sf::Font const & font, unsigned fontSize, std::string const & str) -> Text
{
    Text text(sf::String::fromUtf8(str.cbegin(), str.cend()), font, fontSize);
    return text;
}

sf::Vector2f Text::getTopLeftPosition() const
{
    auto const bounds = getGlobalBounds();
    return { bounds.left, bounds.top };
}

sf::Vector2f Text::getTopRightPosition() const
{
    auto const bounds = getGlobalBounds();
    return { bounds.left + bounds.width, bounds.top };
}

sf::Vector2f Text::getBottomLeftPosition() const
{
    auto const bounds = getGlobalBounds();
    return { bounds.left, bounds.top + bounds.height };
}

sf::Vector2f Text::getBottomRightPosition() const
{
    auto const bounds = getGlobalBounds();
    return { bounds.left + bounds.width, bounds.top + bounds.height };
}

float Text::getGlobalWidth() const
{
    return getGlobalBounds().width;
}

float Text::getGlobalHeight() const
{
    return getGlobalBounds().height;
}

void Text::setCenterOrigin()
{
    setVerticalCenterOrigin();
    setHorizontalCenterOrigin();
}

void Text::setVerticalCenterOrigin()
{
    auto const bounds = getLocalBounds();
    setOrigin(getOrigin().x, std::ceil((bounds.top + bounds.height) / 2));
}

void Text::setHorizontalCenterOrigin()
{
    auto const bounds = getLocalBounds();
    setOrigin(std::ceil((bounds.left + bounds.width) / 2), getOrigin().y);
}

void Text::resetOrigin()
{
    setOrigin(0, 0);
}

void Text::centerIn(sf::Sprite const & source)
{
    centerVertically(source);
    centerHorizontally(source);
}

void Text::centerVertically(sf::Sprite const & source)
{
    auto const b = source.getGlobalBounds();
    auto const y = b.top + (b.height - getGlobalHeight() - getLocalBounds().top) / 2;
    setPosition({ getPosition().x, std::ceil(y) });
}

void Text::centerHorizontally(sf::Sprite const & source)
{
    auto const b = source.getGlobalBounds();
    auto const x = b.left + (b.width - getGlobalWidth() - getLocalBounds().left) / 2;
    setPosition({ std::ceil(x), getPosition().y });
}

void Text::moveUnder(sf::Text const & source, float offsetY)
{
    auto const b = source.getGlobalBounds();
    auto const l = getLocalBounds();
    setPosition({ b.left - l.left, b.top + b.height + offsetY - l.top });
}

void Text::setOutline(sf::Color const & color, float thickness)
{
    setOutlineColor(color);

    auto const oldThickness = getOutlineThickness();
    setOutlineThickness(thickness ? thickness : (oldThickness ? oldThickness : 1.f));
}

void Text::removeOutline()
{
    setOutlineThickness(0);
}
