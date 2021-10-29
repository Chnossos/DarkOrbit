/// @file   SfmlText.hpp
/// @author Pierre Caissial
/// @date   Created on 29/10/2021

#pragma once

namespace sf
{
    class Sprite;
    class Text;
} // !namespace sf

namespace Utils
{
    void setTextPosition (sf::Text & text, float x, float y);
    void centerIn        (sf::Text & dst, sf::Sprite const & src, float x = 0, float y = 0);
    void centerVertically(sf::Text & dst, sf::Sprite const & src, float x,     float y = 0);
} // !namespace Utils
