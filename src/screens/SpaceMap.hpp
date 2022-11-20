/// @file   SpaceMap.hpp
/// @author Pierre Caissial
/// @date   Created on 22/10/2021

#pragma once

// Project includes
#include "../engine/Screen.hpp"
#include "../engine/TextureManager.hpp"
#include "../game/PlayerStats.hpp"
#include "../game/ShipStats.hpp"

namespace Screens { class SpaceMapScreen; }

class Screens::SpaceMapScreen final : public Engine::Screen
{
private:
    Engine::TextureManager _textureManager;
    sf::Vector2u           _miniMapPos;
    Game::PlayerStats      _player;
    Game::ShipStats        _ship;

public:
    SpaceMapScreen() noexcept;

public:
    void enter() override;

public:
    void onEvent(sf::Event const & event) override;
    void draw(sf::RenderTarget & target, sf::RenderStates) const override;
};
