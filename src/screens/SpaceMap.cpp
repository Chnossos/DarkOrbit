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
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
#include <spdlog/spdlog.h>

using namespace Screens;

SpaceMapScreen::SpaceMapScreen() noexcept
    : _player { .level = Formulas::getLevelFromXp(_player.xp) }
{}

void SpaceMapScreen::enter() try
{
    Core::bAssert(_font.loadFromFile(fmt::format("assets/font/{}", Constants::fontFamily)),
                  "Failed to load _font");
    Core::bAssert(_nbFont.loadFromFile(fmt::format("assets/font/{}", Constants::nbFontFamily)),
                  "Failed to load _nbFont");

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
    SPDLOG_ERROR("[SpaceMap] Failed to load some assets");
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

    auto miniMapHeaderLabel = Text::make(_nbFont, Constants::nbFontSize,
                                         "MAP 3-1 /POS {}/{}", _miniMapPos.x, _miniMapPos.y);
    miniMapHeaderLabel.centerVertically(miniMapHeader);
    miniMapHeaderLabel.move(miniMapHeader.getPosition().x + Constants::spacing, 0);

    auto configLabel = Text::make(_font, Constants::subLabelFontSize, "CONFIGURATION");
    configLabel.centerIn(configLabelBg);

    auto config1 = Text::make(_nbFont, Constants::nbFontSize, "1");
    auto config2 = Text::make(_nbFont, Constants::nbFontSize, "2");

    config1.centerIn(configActive);
    config2.centerIn(configInactive);

    auto xpLabel      = Text::make(_font, Constants::labelFontSize, "EXPÉRIENCE");
    auto levelLabel   = Text::make(_font, Constants::labelFontSize, "LEVEL");
    auto honorLabel   = Text::make(_font, Constants::labelFontSize, "HONOR");
    auto jackpotLabel = Text::make(_font, Constants::labelFontSize, "JACKPOT");

    xpLabel.setPosition(248, Constants::startY);
    levelLabel  .moveUnder(xpLabel,    Constants::spacing);
    honorLabel  .moveUnder(levelLabel, Constants::spacing);
    jackpotLabel.moveUnder(honorLabel, Constants::spacing);

    auto xpValue      = Text::make(_nbFont, Constants::valueFontSize, "{:L}", _player.xp);
    auto levelValue   = Text::make(_nbFont, Constants::valueFontSize, "{:L}", _player.level);
    auto honorValue   = Text::make(_nbFont, Constants::valueFontSize, "{:L}", _player.honor);
    auto jackpotValue = Text::make(_nbFont, Constants::valueFontSize, "{:L}", _player.jackpot);

    xpValue     .setOrigin(xpValue     .getBottomRightPosition());
    levelValue  .setOrigin(levelValue  .getBottomRightPosition());
    honorValue  .setOrigin(honorValue  .getBottomRightPosition());
    jackpotValue.setOrigin(jackpotValue.getBottomRightPosition());

    xpValue.setPosition(     415, xpLabel     .getBottomRightPosition().y + 1);
    levelValue.setPosition(  415, levelLabel  .getBottomRightPosition().y);
    honorValue.setPosition(  415, honorLabel  .getBottomRightPosition().y + 1);
    jackpotValue.setPosition(415, jackpotLabel.getBottomRightPosition().y + 1);

    auto creditsLabel = Text::make(_font, Constants::labelFontSize - 1, "CREDITS");
    auto uridiumLabel = Text::make(_font, Constants::labelFontSize - 1, "URIDIUM");
    auto cargoLabel   = Text::make(_font, Constants::labelFontSize - 1, "CARGO BAY");

    creditsLabel.setVerticalCenterOrigin();
    uridiumLabel.setVerticalCenterOrigin();
    cargoLabel  .setVerticalCenterOrigin();

    creditsLabel.setPosition(511, Constants::startY + 6);
    uridiumLabel.setPosition(571, Constants::startY + 6);
    cargoLabel  .setPosition(631, Constants::startY + 6);

    creditsLabel.resetOrigin();
    uridiumLabel.resetOrigin();
    cargoLabel  .resetOrigin();

    auto creditsValue = Text::make(_nbFont, Constants::nbFontSize, "{:L}", _player.credits);
    auto uridiumValue = Text::make(_nbFont, Constants::nbFontSize, "{:L}", _player.uridium);
    auto cargoValue   = Text::make(_nbFont, Constants::nbFontSize, "{:L}", _ship.curCargo);

    creditsValue.moveUnder(creditsLabel, Constants::spacing - 2);
    uridiumValue.moveUnder(uridiumLabel, Constants::spacing - 2);
    cargoValue  .moveUnder(cargoLabel,   Constants::spacing - 2);

    for (sf::Text * t : { &creditsLabel, &creditsValue, &uridiumLabel,
                          &uridiumValue, &cargoLabel,   &cargoValue })
    {
        t->setOrigin(std::ceilf(t->getLocalBounds().width  / 2),
                     std::ceilf(t->getLocalBounds().height / 2));
    }

    auto shieldLabel  = Text::make(_font, Constants::labelFontSize, "SHIELD");
    auto hpLabel      = Text::make(_font, Constants::labelFontSize, "HIT POINTS");
    auto ammoLabel    = Text::make(_font, Constants::labelFontSize, "AMMO");
    auto rocketsLabel = Text::make(_font, Constants::labelFontSize, "ROCKETS");

    hpLabel     .setOrigin(std::ceilf(hpLabel     .getLocalBounds().width), 0.f);
    shieldLabel .setOrigin(std::ceilf(shieldLabel .getLocalBounds().width), 0.f);
    ammoLabel   .setOrigin(std::ceilf(ammoLabel   .getLocalBounds().width), 0.f);
    rocketsLabel.setOrigin(std::ceilf(rocketsLabel.getLocalBounds().width), 0.f);

    shieldLabel .setPosition(shieldAmountBg .getPosition().x - 5,
                             shieldAmountBg .getPosition().y - 5);
    hpLabel     .setPosition(hpAmountBg     .getPosition().x - 5,
                             hpAmountBg     .getPosition().y - 5);
    ammoLabel   .setPosition(ammoAmountBg   .getPosition().x - 5,
                             ammoAmountBg   .getPosition().y - 5);
    rocketsLabel.setPosition(rocketsAmountBg.getPosition().x - 5,
                             rocketsAmountBg.getPosition().y - 5);

    auto shieldValue  = Text::make(_nbFont, Constants::nbFontSize,
                                   "{:L} / {:L}", _ship.curShield, _ship.maxShield);
    auto hpValue      = Text::make(_nbFont, Constants::nbFontSize,
                                   "{:L} / {:L}", _ship.curHp, _ship.maxHp);
    auto ammoValue    = Text::make(_nbFont, Constants::nbFontSize,
                                   "{:L} / {:L}", _ship.curAmmo, _ship.maxAmmo);
    auto rocketsValue = Text::make(_nbFont, Constants::nbFontSize,
                                   "{:L} / {:L}", _ship.curRockets, _ship.maxRockets);

    shieldValue. setOutline(sf::Color::Black);
    hpValue.     setOutline(sf::Color::Black);
    ammoValue.   setOutline(sf::Color::Black);
    rocketsValue.setOutline(sf::Color::Black);

    shieldValue .centerIn(shieldAmountBg);
    hpValue     .centerIn(hpAmountBg);
    ammoValue   .centerIn(ammoAmountBg);
    rocketsValue.centerIn(rocketsAmountBg);

    auto const drawWithBorder = [&target] (auto const & source,
                                           sf::Color const & color = sf::Color::Red)
    {
        auto const bounds = source.getGlobalBounds();

        sf::RectangleShape rect({ bounds.width, bounds.height });
        rect.setPosition(bounds.left, bounds.top);
        rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineColor(color);
        rect.setOutlineThickness(1);

        target.draw(source);
        target.draw(rect);

//        sf::RectangleShape rect2({ bounds.width, bounds.height });
//        rect2.setPosition(source.getPosition());
//        rect2.setFillColor(sf::Color::Transparent);
//        rect2.setOutlineColor(color);
//        rect2.setOutlineThickness(1);
//        target.draw(rect2);
    };

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
