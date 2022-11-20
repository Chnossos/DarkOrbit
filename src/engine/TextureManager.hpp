/// @file   TextureManager.hpp
/// @author Pierre Caissial
/// @date   Created on 22/10/2021

#pragma once

// third-party includes
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

// C++ includes
#include <filesystem>
#include <unordered_map>

namespace Engine { class TextureManager; }

class Engine::TextureManager
{
private:
    std::unordered_map<std::string, sf::Texture> _textures;

public:
    auto load(std::string name, std::filesystem::path const & path) -> sf::Texture &;

public:
    [[nodiscard]] auto sprite(std::string const & name) const -> sf::Sprite;
};
