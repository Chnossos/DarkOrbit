/// @file   Screen.hpp
/// @author Pierre Caissial
/// @date   Created on 22/10/2021

#pragma once

// SFML includes
#include <SFML/Graphics/Drawable.hpp>

namespace sf
{
    class Event;
    class Time;
} // !namespace sf

namespace Engine
{
    class Screen : public sf::Drawable
    {
    public:
        Screen()                      noexcept = default;
        Screen(Screen &&)             noexcept = default;
        Screen & operator=(Screen &&) noexcept = default;
        virtual ~Screen()             noexcept = 0;

    public:
        Screen(Screen const &)             noexcept = delete;
        Screen & operator=(Screen const &) noexcept = delete;

    public:
        virtual void onEvent(sf::Event const  &) {}
        virtual void update (sf::Time  const  &) {}

        /****/  void draw(sf::RenderTarget & target) const { draw(target, sf::RenderStates()); }
        virtual void draw(sf::RenderTarget &, sf::RenderStates) const {}

    public:
        virtual void enter()  {}
        virtual void pause()  {}
        virtual void resume() {}
        virtual void exit()   {}
    };

    inline Screen::~Screen() noexcept = default;
} // !namespace Engine
