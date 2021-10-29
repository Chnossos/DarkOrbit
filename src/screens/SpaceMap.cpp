/// @file   SpaceMap.cpp
/// @author Pierre Caissial
/// @date   Created on 22/10/2021

#include "SpaceMap.hpp"

// Project includes
#include "../core/Constants.hpp"
#include "../core/Exception.hpp"
#include "../game/Formulas.hpp"
#include "../utils/Factories.hpp"
#include "../utils/SfmlText.hpp"

// SFML includes
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

// Third-party includes
#include <spdlog/spdlog.h>

using namespace Screens;
using namespace Utils;
using Formulas::getLevelFromXp;

SpaceMapScreen::SpaceMapScreen() noexcept
    : _miniMapPos{0, 0}
{}

void SpaceMapScreen::enter() try
{
    spdlog::trace("[SpaceMap] Loading textures");
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
    spdlog::trace("[SpaceMap] Loading done");
}
catch (...)
{
    spdlog::error("[SpaceMap] Failed to load textures");
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

    hpAmountBg    .setPosition(514, 57);
    shieldAmountBg.setPosition(514, 42);
    ammoAmountBg  .setPosition(686, 42);
    rocketsAmountBg.setPosition(686, 57);

    for (auto && s : { &hpAmountBg, &shieldAmountBg, &ammoAmountBg, &rocketsAmountBg })
        s->setColor(sf::Color(255, 255, 255, 120));

    // TEXT

    constexpr auto startY  = 10;
    constexpr auto spacing = 10;

    sf::Font font;
    Core::bAssert(font.loadFromFile("assets/font/orbitron-bold.ttf"), "Failed to load font");

    sf::Text miniMapHeaderLabel("MAP\t\t\t/POS", font, Constants::fontSize);
    centerVertically(miniMapHeaderLabel, miniMapHeader, miniMapHeader.getPosition().x + 6);

    auto const pos = fmt::format("\t\t{}/{}", _miniMapPos.x, _miniMapPos.y);
    sf::Text miniMapPosition(pos, font, Constants::fontSize);
    centerVertically(miniMapPosition, miniMapHeader,
         miniMapHeaderLabel.getPosition().x + miniMapHeaderLabel.getLocalBounds().width);

    sf::Text configLabel("CONFIGURATION", font, Constants::fontSize);
    centerIn(configLabel, configLabelBg);

    sf::Text config1("1", font, Constants::fontSize), config2("2", font, Constants::fontSize);
    centerIn(config1, configActive, 0, 1);
    centerIn(config2, configInactive);

    sf::Text xpLabel     ("EXPERIENCE", font, Constants::fontSize + 1);
    sf::Text levelLabel  ("LEVEL",      font, Constants::fontSize + 1);
    sf::Text honorLabel  ("HONOR",      font, Constants::fontSize + 1);
    sf::Text jackpotLabel("JACKPOT",    font, Constants::fontSize + 1);

    setTextPosition(xpLabel,      248, startY);
    setTextPosition(levelLabel,   248, xpLabel   .getPosition().y + Constants::fontSize + spacing);
    setTextPosition(honorLabel,   248, levelLabel.getPosition().y + Constants::fontSize + spacing);
    setTextPosition(jackpotLabel, 248, honorLabel.getPosition().y + Constants::fontSize + spacing);

    sf::Text xpValue     (fmt::format("{:L}", _player.xp),                 font, Constants::fontSize);
    sf::Text levelValue  (fmt::format("{:L}", getLevelFromXp(_player.xp)), font, Constants::fontSize);
    sf::Text honorValue  (fmt::format("{:L}", _player.honor),              font, Constants::fontSize);
    sf::Text jackpotValue(fmt::format("{:L}", _player.jackpot),            font, Constants::fontSize);

    xpValue     .setOrigin((int)xpValue     .getLocalBounds().width, 0);
    levelValue  .setOrigin((int)levelValue  .getLocalBounds().width, 0);
    honorValue  .setOrigin((int)honorValue  .getLocalBounds().width, 0);
    jackpotValue.setOrigin((int)jackpotValue.getLocalBounds().width, 0);

    setTextPosition(xpValue,      415, startY);
    setTextPosition(levelValue,   xpValue.getPosition().x,
                                  xpValue.getPosition().y + Constants::fontSize + spacing);
    setTextPosition(honorValue,   xpValue.getPosition().x,
                                  levelValue.getPosition().y + Constants::fontSize + spacing);
    setTextPosition(jackpotValue, xpValue.getPosition().x,
                                  honorValue.getPosition().y + Constants::fontSize + spacing);

    sf::Text creditsLabel("CREDITS", font, Constants::fontSize + 1);
    sf::Text creditsValue(fmt::format("{:L}", _player.credits), font, Constants::fontSize);

    setTextPosition(creditsLabel, 510, startY);
    setTextPosition(creditsValue, creditsLabel.getPosition().x,
                                  creditsLabel.getPosition().y + Constants::fontSize + spacing - 2);

    sf::Text uridiumLabel("URIDIUM", font, Constants::fontSize + 1);
    sf::Text uridiumValue(fmt::format("{:L}", _player.uridium), font, Constants::fontSize);

    setTextPosition(uridiumLabel, 580, startY);
    setTextPosition(uridiumValue, uridiumLabel.getPosition().x,
                                  uridiumLabel.getPosition().y + Constants::fontSize + spacing - 2);

    sf::Text cargoLabel("CARGO BAY", font, Constants::fontSize + 1);
    sf::Text cargoValue(fmt::format("{:L}", _ship.curCargo), font, Constants::fontSize);

    setTextPosition(cargoLabel, 670 - cargoLabel.getLocalBounds().width / 2, startY);
    setTextPosition(cargoValue, cargoLabel.getPosition().x,
                                cargoLabel.getPosition().y + Constants::fontSize + spacing - 2);

    for (auto && t : { &creditsLabel, &creditsValue, &uridiumLabel,
                       &uridiumValue, &cargoLabel,   &cargoValue })
    {
        t->setOrigin((int)t->getLocalBounds().width / 2, (int)t->getLocalBounds().height / 2);
    }

    sf::Text shieldLabel("SHIELD", font, Constants::fontSize + 1);
    shieldLabel.setOrigin((int)shieldLabel.getLocalBounds().width, 0);
    shieldLabel.setPosition(shieldAmountBg.getPosition().x - 5, shieldAmountBg.getPosition().y - 2);

    sf::Text hpLabel("HIT POINTS", font, Constants::fontSize + 1);
    hpLabel.setOrigin((int)hpLabel.getLocalBounds().width, 0);
    hpLabel.setPosition(hpAmountBg.getPosition().x - 5, hpAmountBg.getPosition().y - 1);

    sf::Text ammoLabel("AMMO", font, Constants::fontSize + 1);
    ammoLabel.setOrigin((int)ammoLabel.getLocalBounds().width, 0);
    ammoLabel.setPosition(ammoAmountBg.getPosition().x - 5, ammoAmountBg.getPosition().y - 1);

    sf::Text rocketsLabel("ROCKETS", font, Constants::fontSize + 1);
    rocketsLabel.setOrigin((int)rocketsLabel.getLocalBounds().width, 0);
    rocketsLabel.setPosition(rocketsAmountBg.getPosition().x - 5, rocketsAmountBg.getPosition().y - 1);

    auto shieldValue = Utils::makeText(font, "{:L} / {:L}", _ship.curShield, _ship.maxShield);
    centerIn(shieldValue, shieldAmountBg);

    auto hpValue = Utils::makeText(font, "{:L} / {:L}", _ship.curHp, _ship.maxHp);
    centerIn(hpValue, hpAmountBg);

    auto ammoValue = Utils::makeText(font, "{:L} / {:L}", _ship.curAmmo, _ship.maxAmmo);
    centerIn(ammoValue, ammoAmountBg);

    auto rocketsValue = Utils::makeText(font, "{:L} / {:L}", _ship.curRockets, _ship.maxRockets);
    centerIn(rocketsValue, rocketsAmountBg);

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
catch (std::exception const & e)
{
    spdlog::error("Failed to draw frame:\n{}", Core::formatExceptionStack(e));
}
