/// @file   TextureManager.cpp
/// @author Pierre Caissial
/// @date   Created on 22/10/2021

#include "TextureManager.hpp"

// Project includes
#include "../core/Exception.hpp"

using namespace Engine;

auto TextureManager::load(std::string name, std::filesystem::path const & path) -> sf::Texture &
{
    auto & texture = _textures.try_emplace(std::move(name)).first->second;
    Core::bAssert(texture.loadFromFile(path.string()),
                  "Failed to load texture '{}' from {}", name, path.string());
    return texture;
}

auto TextureManager::sprite(std::string const & name) const -> sf::Sprite
{
    sf::Sprite sprite;
    Core::bAssert(_textures.contains(name), "No texture loaded for '{}'", name);
    sprite.setTexture(_textures.at(name));
    return sprite;
}
