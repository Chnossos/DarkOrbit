/// @file   SpaceMap.hpp
/// @author Pierre Caissial
/// @date   Created on 22/10/2021

#pragma once

// Project includes
#include "../engine/Screen.hpp"
#include "../engine/TextureManager.hpp"

namespace Screens { class SpaceMapScreen; }

class Screens::SpaceMapScreen final : public Engine::Screen
{
private:
    Engine::TextureManager _textureManager;
    sf::Vector2u _miniMapPos;

public:
    SpaceMapScreen() noexcept;

public:
    void enter() override;

public:
    void onEvent(sf::Event const & event) override;
    void update(sf::Time const & time) override;
    void draw(sf::RenderTarget & target) override;
};
