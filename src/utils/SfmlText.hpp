/// @file   SfmlText.hpp
/// @author Pierre Caissial
/// @date   Created on 29/10/2021

#pragma once

// Third-party includes
#include <fmt/format.h>
#include <SFML/Graphics/Text.hpp>

namespace sf
{
    class Color;
    class Font;
    class Sprite;
} // !namespace sf

class Text : public sf::Text
{
protected:
    using sf::Text::Text;

public:
    static auto make(sf::Font const & font, unsigned fontSize, std::string const & str) -> Text;

    template<typename... Args>
    static auto make(sf::Font const & font, unsigned fontSize,
                         fmt::format_string<Args...> str, Args &&... args)
    {
        auto const text = fmt::format(std::move(str), std::forward<Args>(args)...);
        return make(font, fontSize, text);
    }

public:
    sf::Vector2f getTopLeftPosition() const;
    sf::Vector2f getTopRightPosition() const;
    sf::Vector2f getBottomLeftPosition() const;
    sf::Vector2f getBottomRightPosition() const;
    float getGlobalWidth() const;
    float getGlobalHeight() const;

public:
    void setCenterOrigin();
    void setVerticalCenterOrigin();
    void setHorizontalCenterOrigin();
    void resetOrigin();
    void centerIn(sf::Sprite const & source);
    void centerVertically(sf::Sprite const & source);
    void centerHorizontally(sf::Sprite const & source);
    void moveUnder(sf::Text const & source, float offsetY);

public:
    void setOutline(sf::Color const & color, float thickness = 0);
    void removeOutline();
};
