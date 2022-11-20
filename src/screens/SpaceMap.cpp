/// @file   SpaceMap.cpp
/// @author Pierre Caissial
/// @date   Created on 22/10/2021

#include "SpaceMap.hpp"

// Project includes
#include "../core/Constants.hpp"
#include "../core/Exception.hpp"
#include "../game/Formulas.hpp"
#include "../utils/SfmlText.hpp"

// Third-party includes
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <spdlog/spdlog.h>

using namespace Screens;
using namespace Utils;

SpaceMapScreen::SpaceMapScreen() noexcept
    : _player { .level = Formulas::getLevelFromXp(_player.xp) }
{}

void SpaceMapScreen::enter() try
{
    Core::bAssert(_font.loadFromFile(fmt::format("assets/font/{}", Constants::fontFamily)),
                  "Failed to load _font");

    SPDLOG_DEBUG("[SpaceMap] Loading textures");
    _textureManager.load("header",                "assets/ui/header.png");
    _textureManager.load("ammo_rocket_amount_bg", "assets/ui/ammo_rocket_amount_bg.png");
    _textureManager.load("hp_amount_bg",          "assets/ui/hit_points_amount_bg.png");
    _textureManager.load("shield_amount_bg",      "assets/ui/shield_amount_bg.png");
    _textureManager.load("mini-map",              "assets/ui/mini-map.jpg");
    _textureManager.load("mini-map_header",       "assets/ui/mini-map_header.png");
    _textureManager.load("config_label",          "assets/ui/configuration_label_bg.png");
    _textureManager.load("config_active",         "assets/ui/configuration_active.png");
    _textureManager.load("config_inactive",       "assets/ui/configuration_inactive.png");
    _textureManager.load("inventory_right",       "assets/ui/inventory_right.jpg");
    _textureManager.load("inventory_center",      "assets/ui/inventory_center.jpg");
    _textureManager.load("inventory_left",        "assets/ui/inventory_left.png");
    _textureManager.load("inventory_triangle",    "assets/ui/inventory_triangle.png");
    _textureManager.load("inventory_content_bg",  "assets/ui/inventory_content_bg.png");
    SPDLOG_DEBUG("[SpaceMap] Loading done");
}
catch (...)
{
    SPDLOG_ERROR("[SpaceMap] Failed to load textures");
}

void SpaceMapScreen::onEvent(sf::Event const & event)
{
    if (event.type == sf::Event::MouseMoved)
    {
        _miniMapPos.x = event.mouseMove.x;
        _miniMapPos.y = event.mouseMove.y;
    }
}

void SpaceMapScreen::draw(sf::RenderTarget & target, sf::RenderStates) const try
{
    auto header = _textureManager.sprite("header");

    auto miniMap = _textureManager.sprite("mini-map");
    miniMap.setPosition(target.getSize().x - miniMap.getLocalBounds().width,
                        target.getSize().y - miniMap.getLocalBounds().height);

    auto miniMapHeader = _textureManager.sprite("mini-map_header");
    miniMapHeader.setPosition(
        target .getSize()    .x - miniMapHeader.getLocalBounds().width + 5,
        miniMap.getPosition().y - miniMapHeader.getLocalBounds().height
    );

    auto configInactive = _textureManager.sprite("config_inactive");
    configInactive.setPosition(
        target       .getSize()    .x - configInactive.getLocalBounds().width,
        miniMapHeader.getPosition().y - configInactive.getLocalBounds().height
    );

    auto configActive = _textureManager.sprite("config_active");
    configActive.setPosition(
        configInactive.getPosition().x - configActive.getLocalBounds().width,
        miniMapHeader .getPosition().y - configActive.getLocalBounds().height
    );

    auto configLabelBg = _textureManager.sprite("config_label");
    configLabelBg.setPosition(
        configActive .getPosition().x - configLabelBg.getLocalBounds().width,
        miniMapHeader.getPosition().y - configLabelBg.getLocalBounds().height
    );

    auto inventoryRight = _textureManager.sprite("inventory_right");
    inventoryRight.setPosition(
        miniMap.getPosition().x - inventoryRight.getLocalBounds().width,
        target .getSize()    .y - inventoryRight.getLocalBounds().height
    );

    auto inventoryCenter = _textureManager.sprite("inventory_center");
    inventoryCenter.setPosition(
        inventoryRight.getPosition().x - inventoryCenter.getLocalBounds().width,
        inventoryRight.getPosition().y
    );

    auto inventoryLeft = _textureManager.sprite("inventory_left");
    inventoryLeft.setPosition(
        inventoryCenter.getPosition().x - inventoryLeft.getLocalBounds().width,
        inventoryCenter.getPosition().y
    );

    auto inventoryTriangle = _textureManager.sprite("inventory_triangle");
    inventoryTriangle.setPosition(
        inventoryRight.getPosition().x - inventoryTriangle.getLocalBounds().width,
        inventoryRight.getPosition().y - inventoryTriangle.getLocalBounds().height
    );

    auto inventoryContentBg = _textureManager.sprite("inventory_content_bg");
    inventoryContentBg.setPosition(370, 579);

    auto ammoAmountBg    = _textureManager.sprite("ammo_rocket_amount_bg");
    auto rocketsAmountBg = _textureManager.sprite("ammo_rocket_amount_bg");
    auto hpAmountBg      = _textureManager.sprite("hp_amount_bg");
    auto shieldAmountBg  = _textureManager.sprite("shield_amount_bg");

    hpAmountBg     .setPosition(514, 57);
    shieldAmountBg .setPosition(514, 42);
    ammoAmountBg   .setPosition(686, 42);
    rocketsAmountBg.setPosition(686, 57);

    for (auto && s : { &hpAmountBg, &shieldAmountBg, &ammoAmountBg, &rocketsAmountBg })
        s->setColor(sf::Color(255, 255, 255, 120));

    // TEXT

    constexpr auto startY  = 8;
    constexpr auto spacing = 10;

    auto miniMapHeaderLabel = makeText(_font, "MAP\t\t\t/POS");
    centerVertically(miniMapHeaderLabel, miniMapHeader, miniMapHeader.getPosition().x + 6);

    auto miniMapPosition = makeText(_font, "\t\t{}/{}", _miniMapPos.x, _miniMapPos.y);
    centerVertically(miniMapPosition, miniMapHeader,
         miniMapHeaderLabel.getPosition().x + miniMapHeaderLabel.getLocalBounds().width);

    auto configLabel = makeText(_font, "CONFIGURATION");
    centerIn(configLabel, configLabelBg);

    auto config1 = makeText(_font, "1");
    auto config2 = makeText(_font, "2");

    centerIn(config1, configActive, 0, 1);
    centerIn(config2, configInactive);

    auto xpLabel      = makeText(_font, "EXPERIENCE");
    auto levelLabel   = makeText(_font, "LEVEL");
    auto honorLabel   = makeText(_font, "HONOR");
    auto jackpotLabel = makeText(_font, "JACKPOT");

    setTextPosition(xpLabel,      248, startY);
    setTextPosition(levelLabel,   248, xpLabel   .getPosition().y + Constants::fontSize + spacing);
    setTextPosition(honorLabel,   248, levelLabel.getPosition().y + Constants::fontSize + spacing);
    setTextPosition(jackpotLabel, 248, honorLabel.getPosition().y + Constants::fontSize + spacing);

    auto xpValue      = makeText(_font, "{:L}", _player.xp);
    auto levelValue   = makeText(_font, "{:L}", _player.level);
    auto honorValue   = makeText(_font, "{:L}", _player.honor);
    auto jackpotValue = makeText(_font, "{:L}", _player.jackpot);

    xpValue     .setOrigin(std::ceilf(xpValue     .getLocalBounds().width), 0.f);
    levelValue  .setOrigin(std::ceilf(levelValue  .getLocalBounds().width), 0.f);
    honorValue  .setOrigin(std::ceilf(honorValue  .getLocalBounds().width), 0.f);
    jackpotValue.setOrigin(std::ceilf(jackpotValue.getLocalBounds().width), 0.f);

    setTextPosition(xpValue,      415,                     xpLabel     .getGlobalBounds().top);
    setTextPosition(levelValue,   xpValue.getPosition().x, levelLabel  .getGlobalBounds().top);
    setTextPosition(honorValue,   xpValue.getPosition().x, honorLabel  .getGlobalBounds().top);
    setTextPosition(jackpotValue, xpValue.getPosition().x, jackpotLabel.getGlobalBounds().top);

    auto creditsLabel = makeText(_font, "CREDITS");
    auto uridiumLabel = makeText(_font, "URIDIUM");
    auto cargoLabel   = makeText(_font, "CARGO BAY");

    auto creditsValue = makeText(_font, "{:L}", _player.credits);
    auto uridiumValue = makeText(_font, "{:L}", _player.uridium);
    auto cargoValue   = makeText(_font, "{:L}", _ship.curCargo);

    setTextPosition(creditsLabel, 510,                                         startY + 2);
    setTextPosition(uridiumLabel, 580,                                         startY + 2);
    setTextPosition(cargoLabel,   670 - cargoLabel.getLocalBounds().width / 2, startY + 2);

    setTextPosition(creditsValue, creditsLabel.getPosition().x,
                                  creditsLabel.getPosition().y + Constants::fontSize + spacing - 2);
    setTextPosition(uridiumValue, uridiumLabel.getPosition().x,
                                  uridiumLabel.getPosition().y + Constants::fontSize + spacing - 2);
    setTextPosition(cargoValue,   cargoLabel  .getPosition().x,
                                  cargoLabel  .getPosition().y + Constants::fontSize + spacing - 2);

    for (sf::Text * t : { &creditsLabel, &creditsValue, &uridiumLabel,
                          &uridiumValue, &cargoLabel,   &cargoValue })
    {
        t->setOrigin(std::ceilf(t->getLocalBounds().width  / 2),
                     std::ceilf(t->getLocalBounds().height / 2));
    }

    auto shieldLabel  = makeText(_font, "SHIELD");
    auto hpLabel      = makeText(_font, "HIT POINTS");
    auto ammoLabel    = makeText(_font, "AMMO");
    auto rocketsLabel = makeText(_font, "ROCKETS");

    hpLabel     .setOrigin(std::ceilf(hpLabel     .getLocalBounds().width), 0.f);
    shieldLabel .setOrigin(std::ceilf(shieldLabel .getLocalBounds().width), 0.f);
    ammoLabel   .setOrigin(std::ceilf(ammoLabel   .getLocalBounds().width), 0.f);
    rocketsLabel.setOrigin(std::ceilf(rocketsLabel.getLocalBounds().width), 0.f);

    shieldLabel .setPosition(shieldAmountBg .getPosition().x - 5,
                             shieldAmountBg .getPosition().y - 2);
    hpLabel     .setPosition(hpAmountBg     .getPosition().x - 5,
                             hpAmountBg     .getPosition().y - 1);
    ammoLabel   .setPosition(ammoAmountBg   .getPosition().x - 5,
                             ammoAmountBg   .getPosition().y - 1);
    rocketsLabel.setPosition(rocketsAmountBg.getPosition().x - 5,
                             rocketsAmountBg.getPosition().y - 1);

    auto shieldValue  = makeText(_font, "{:L} / {:L}", _ship.curShield,  _ship.maxShield);
    auto hpValue      = makeText(_font, "{:L} / {:L}", _ship.curHp,      _ship.maxHp);
    auto ammoValue    = makeText(_font, "{:L} / {:L}", _ship.curAmmo,    _ship.maxAmmo);
    auto rocketsValue = makeText(_font, "{:L} / {:L}", _ship.curRockets, _ship.maxRockets);

    setOutline(shieldValue,  sf::Color::Black);
    setOutline(hpValue,      sf::Color::Black);
    setOutline(ammoValue,    sf::Color::Black);
    setOutline(rocketsValue, sf::Color::Black);

    centerIn(shieldValue,  shieldAmountBg,  0, 1);
    centerIn(hpValue,      hpAmountBg,      0, 1);
    centerIn(ammoValue,    ammoAmountBg,    0, 1);
    centerIn(rocketsValue, rocketsAmountBg, 0, 1);

    target.draw(header);
    target.draw(hpAmountBg);
    target.draw(shieldAmountBg);
    target.draw(ammoAmountBg);
    target.draw(rocketsAmountBg);
    target.draw(miniMap);
    target.draw(miniMapHeader);
    target.draw(configLabelBg);
    target.draw(configActive);
    target.draw(configInactive);
    target.draw(inventoryRight);
    target.draw(inventoryCenter);
    target.draw(inventoryLeft);
    target.draw(inventoryTriangle);
    target.draw(inventoryContentBg);
    // Draw text on top
    target.draw(miniMapHeaderLabel);
    target.draw(miniMapPosition);
    target.draw(configLabel);
    target.draw(config1);
    target.draw(config2);
    target.draw(xpLabel);
    target.draw(xpValue);
    target.draw(levelLabel);
    target.draw(levelValue);
    target.draw(honorLabel);
    target.draw(honorValue);
    target.draw(jackpotLabel);
    target.draw(jackpotValue);
    target.draw(creditsLabel);
    target.draw(creditsValue);
    target.draw(uridiumLabel);
    target.draw(uridiumValue);
    target.draw(cargoLabel);
    target.draw(cargoValue);
    target.draw(shieldLabel);
    target.draw(shieldValue);
    target.draw(hpLabel);
    target.draw(hpValue);
    target.draw(ammoLabel);
    target.draw(ammoValue);
    target.draw(rocketsLabel);
    target.draw(rocketsValue);
}
catch (...)
{
    THROW_NESTED("Failed to draw frame");
}
