#include "engine/ScreenManager.hpp"
#include "core/Exception.hpp"

//#include <SFML/Graphics/Font.hpp>
//#include <SFML/Graphics/RenderWindow.hpp>
//#include <SFML/Graphics/Text.hpp>
//#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <spdlog/spdlog.h>

struct PlayerStats
{
    uint64_t xp = 1'999'888'777'666, honor = 111'222'333, credits = 999'999'999;
    uint32_t uridium = 99'999'999;
    uint16_t jackpot = 10'000;
} playerStats;

struct ShipStats
{
    uint32_t hp = 236'000, shield = 320'000, ammo = 220'000, cargo = 999'999;
    uint16_t rockets = 64'000;
} shipStats;

constexpr int getLevelFromXp(uint64_t xp)
{
    int lvl = 1;
    while (xp >= 10'000)
    {
        xp /= 2;
        ++lvl;
    }
    return lvl;
}

//class TextureManager
//{
//private:
//    std::unordered_map<std::string, sf::Texture> _textures;
//
//public:
//    auto load(std::string name, boost::filesystem::path const & path) -> sf::Texture &
//    {
//        auto & texture = _textures.try_emplace(std::move(name)).first->second;
//        bAssert(texture.loadFromFile(path.string()),
//                "Failed to load font '{}' from {}", name, path.string());
//        return texture;
//    }
//
//    auto sprite(std::string const & name) const -> sf::Sprite
//    {
//        bAssert(_textures.contains(name), "No texture loaded for '{}'", name);
//        return sf::Sprite(_textures.at(name));
//    }
//};

int main() try
{
    std::locale::global(std::locale(""));

#ifndef NDEBUG
    spdlog::set_level(spdlog::level::debug);
#endif
    spdlog::set_pattern("%C-%m-%d %H:%M:%S.%e [%t] [%^%L%$] %v");

    sf::VideoMode       videoMode(820, 615, sf::VideoMode::getDesktopMode().bitsPerPixel);
    sf::ContextSettings contextSettings(videoMode.bitsPerPixel);
    constexpr auto      windowStyle = sf::Style::Default;
    sf::RenderWindow    window(videoMode, "Dark Orbit", windowStyle, contextSettings);
    window.setVerticalSyncEnabled(true);

    auto const aspectRatio = (float)videoMode.width / (float)videoMode.height;

//    TextureManager textureMgr;
//
//    auto const & headerTexture             = textureMgr.load("header",
//                                                             "assets/ui/header.png");
//    auto const & ammoRocketAmountBgTexture = textureMgr.load("ammo_rocket_amount_bg",
//                                                             "assets/ui/ammo_rocket_amount_bg.png");
//    auto const & hpAmounBgTexture          = textureMgr.load("hp_amount_bg",
//                                                             "assets/ui/hit_points_amount_bg.png");
//    auto const & shieldBgTexture           = textureMgr.load("shield_amount_bg",
//                                                             "assets/ui/shield_amount_bg.png");
//    auto const & miniMapTexture            = textureMgr.load("mini-map",
//                                                             "assets/ui/mini-map.jpg");
//    auto const & miniMapHeaderTexture      = textureMgr.load("mini-map_header",
//                                                             "assets/ui/mini-map_header.png");
//    auto const & configLabelBgTexture      = textureMgr.load("config_label",
//                                                             "assets/ui/configuration_label_bg.png");
//    auto const & configActiveTexture       = textureMgr.load("config_active",
//                                                             "assets/ui/configuration_active.png");
//    auto const & configInactiveTexture     = textureMgr.load("config_inactive",
//                                                             "assets/ui/configuration_inactive.png");
//    auto const & inventoryRightTexture     = textureMgr.load("inventory_right",
//                                                             "assets/ui/inventory_right.jpg");
//    auto const & inventoryCenterTexture    = textureMgr.load("inventory_center",
//                                                             "assets/ui/inventory_center.jpg");
//    auto const & inventoryLeftTexture      = textureMgr.load("inventory_left",
//                                                             "assets/ui/inventory_left.png");
//    auto const & inventoryTriangleTexture  = textureMgr.load("inventory_triangle",
//                                                             "assets/ui/inventory_triangle.png");
//    auto const & inventoryContentBgTexture = textureMgr.load("inventory_content_bg",
//                                                             "assets/ui/inventory_content_bg.png");
//
//    auto header = textureMgr.sprite("header");
//
//    auto ammoAmountBg   = textureMgr.sprite("ammo_rocket_amount_bg");
//    auto rocketAmountBg = textureMgr.sprite("ammo_rocket_amount_bg");
//    auto hpAmountBg     = textureMgr.sprite("hp_amount_bg");
//    auto shieldAmountBg = textureMgr.sprite("shield_amount_bg");
//
//    hpAmountBg    .setPosition(514, 57);
//    shieldAmountBg.setPosition(514, 42);
//    ammoAmountBg  .setPosition(686, 42);
//    rocketAmountBg.setPosition(686, 57);
//
//    for (auto && s : { &hpAmountBg, &shieldAmountBg, &ammoAmountBg, &rocketAmountBg })
//        s->setColor(sf::Color(255, 255, 255, 150));
//
//    auto miniMap = textureMgr.sprite("mini-map");
//    miniMap.setPosition(static_cast<float>(window.getSize().x - miniMapTexture.getSize().x),
//                        static_cast<float>(window.getSize().y - miniMapTexture.getSize().y));
//
//    auto miniMapHeader = textureMgr.sprite("mini-map_header");
//    miniMapHeader.setPosition(
//        static_cast<float>(window.getSize().x - miniMapHeaderTexture.getSize().x) + 5,
//        miniMap.getPosition().y - static_cast<float>(miniMapHeaderTexture.getSize().y)
//    );
//
//    auto configInactive = textureMgr.sprite("config_inactive");
//    configInactive.setPosition(
//        static_cast<float>(window.getSize().x - configInactiveTexture.getSize().x),
//        miniMapHeader.getPosition().y - static_cast<float>(configInactiveTexture.getSize().y)
//    );
//
//    auto configActive = textureMgr.sprite("config_active");
//    configActive.setPosition(
//        configInactive.getPosition().x - static_cast<float>(configActiveTexture.getSize().x),
//        miniMapHeader.getPosition().y - static_cast<float>(configActiveTexture.getSize().y)
//    );
//
//    auto configLabelBg = textureMgr.sprite("config_label");
//    configLabelBg.setPosition(
//        configActive.getPosition().x - static_cast<float>(configLabelBgTexture.getSize().x),
//        miniMapHeader.getPosition().y - static_cast<float>(configLabelBgTexture.getSize().y)
//    );
//
//    auto inventoryRight = textureMgr.sprite("inventory_right");
//    inventoryRight.setPosition(
//        miniMap.getPosition().x - static_cast<float>(inventoryRightTexture.getSize().x),
//        static_cast<float>(window.getSize().y - inventoryRightTexture.getSize().y)
//    );
//
//    auto inventoryCenter = textureMgr.sprite("inventory_center");
//    inventoryCenter.setPosition(
//        inventoryRight.getPosition().x - static_cast<float>(inventoryCenterTexture.getSize().x),
//        inventoryRight.getPosition().y
//    );
//
//    auto inventoryLeft = textureMgr.sprite("inventory_left");
//    inventoryLeft.setPosition(
//        inventoryCenter.getPosition().x - static_cast<float>(inventoryLeftTexture.getSize().x),
//        inventoryCenter.getPosition().y
//    );
//
//    auto inventoryTriangle = textureMgr.sprite("inventory_triangle");
//    inventoryTriangle.setPosition(
//        inventoryRight.getPosition().x - static_cast<float>(inventoryTriangleTexture.getSize().x),
//        inventoryRight.getPosition().y - static_cast<float>(inventoryTriangleTexture.getSize().y)
//    );
//
//    auto inventoryContentBg = textureMgr.sprite("inventory_content_bg");
//    inventoryContentBg.setPosition(370, 579);
//
//    // TEXT
//
//    constexpr auto startY   = 8;
//    constexpr auto fontSize = 10;
//    constexpr auto spacing  = 4;
//
//    sf::Font font;
//    bAssert(font.loadFromFile("assets/font/vudotronic.ttf"), "Failed to load font");
//
//    sf::Text miniMapHeaderLabel("MAP\t\t\t/POS", font, fontSize);
//    miniMapHeaderLabel.setPosition(miniMapHeader.getPosition().x + 6,
//                                   miniMapHeader.getPosition().y);
//
//    sf::Text miniMapPosition("\t\t0/0", font, fontSize);
//    miniMapPosition.setPosition(
//        miniMapHeaderLabel.getPosition().x + miniMapHeaderLabel.getLocalBounds().width,
//        miniMapHeaderLabel.getPosition().y
//    );
//
//    sf::Text configLabel("CONFIGURATION", font, fontSize);
//    configLabel.setPosition(configLabelBg.getPosition().x + 6,
//                            configLabelBg.getPosition().y);
//
//    sf::Text config1("1", font, fontSize), config2("2", font, fontSize);
//    config1.setPosition(configActive.getPosition().x + 5,
//                        configActive.getPosition().y);
//    config2.setPosition(configInactive.getPosition().x + 5,
//                        configInactive.getPosition().y);
//
//    sf::Text xpLabel("EXPERIENCE", font, fontSize);
//    sf::Text levelLabel("LEVEL", font, fontSize);
//    sf::Text honorLabel("HONOR", font, fontSize);
//    sf::Text jackpotLabel("JACKPOT", font, fontSize);
//
//    xpLabel     .setPosition(248, startY);
//    levelLabel  .setPosition(248, xpLabel.getPosition().y + fontSize + spacing);
//    honorLabel  .setPosition(248, levelLabel.getPosition().y + fontSize + spacing);
//    jackpotLabel.setPosition(248, honorLabel.getPosition().y + fontSize + spacing);
//
//    sf::Text xpValue     (fmt::format("{:L}", playerStats.xp),                 font, fontSize);
//    sf::Text levelValue  (fmt::format("{:L}", getLevelFromXp(playerStats.xp)), font, fontSize);
//    sf::Text honorValue  (fmt::format("{:L}", playerStats.honor),              font, fontSize);
//    sf::Text jackpotValue(fmt::format("{:L}", playerStats.jackpot),            font, fontSize);
//
//    xpValue     .setOrigin(xpValue     .getLocalBounds().width, 0);
//    levelValue  .setOrigin(levelValue  .getLocalBounds().width, 0);
//    honorValue  .setOrigin(honorValue  .getLocalBounds().width, 0);
//    jackpotValue.setOrigin(jackpotValue.getLocalBounds().width, 0);
//
//    xpValue.setPosition(415, startY);
//    levelValue.setPosition(xpValue.getPosition().x,
//                           xpValue.getPosition().y + fontSize + spacing);
//    honorValue.setPosition(xpValue.getPosition().x,
//                           levelValue.getPosition().y + fontSize + spacing);
//    jackpotValue.setPosition(xpValue.getPosition().x,
//                             honorValue.getPosition().y + fontSize + spacing);
//
//    sf::Text creditsLabel("CREDITS", font, fontSize);
//    sf::Text creditsValue(fmt::format("{:L}", playerStats.credits), font, fontSize);
//
//    creditsLabel.setPosition(510, startY);
//    creditsValue.setPosition(creditsLabel.getPosition().x,
//                             creditsLabel.getPosition().y + fontSize + spacing - 2);
//
//    sf::Text uridiumLabel("URIDIUM", font, fontSize);
//    sf::Text uridiumValue(fmt::format("{:L}", playerStats.uridium), font, fontSize);
//
//    uridiumLabel.setPosition(580, startY);
//    uridiumValue.setPosition(uridiumLabel.getPosition().x,
//                             uridiumLabel.getPosition().y + fontSize + spacing - 2);
//
//    sf::Text cargoLabel("CARGO BAY", font, fontSize);
//    sf::Text cargoValue(fmt::format("{:L}", shipStats.cargo), font, fontSize);
//
//    cargoLabel.setPosition(670 - cargoLabel.getLocalBounds().width / 2, startY);
//    cargoValue.setPosition(cargoLabel.getPosition().x,
//                           cargoLabel.getPosition().y + fontSize + spacing - 2);
//
//    for (auto && t : { &creditsLabel, &creditsValue, &uridiumLabel,
//                       &uridiumValue, &cargoLabel,   &cargoValue })
//    {
//        t->setOrigin(t->getLocalBounds().width / 2, t->getLocalBounds().height / 2);
//    }

    Engine::ScreenManager screenManager;
    sf::RenderTexture     gameTexture;
    sf::Clock             clock;

    Core::bAssert(gameTexture.create(videoMode.width, videoMode.height, contextSettings),
                  "Failed to create game texture");

    while (window.isOpen())
    {
        auto const screen = screenManager.top();

        sf::Event event; // NOLINT
        while (window.pollEvent(event))
        {
            /**/ if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::Resized)
            {
                if (event.size.width < videoMode.width || event.size.height < videoMode.height)
                {
                    window.setSize({ videoMode.width, videoMode.height });
                    continue;
                }

                float const new_width     = aspectRatio * event.size.height;
                float const new_height    = event.size.width / aspectRatio;
                float const offset_width  = (event.size.width  - new_width ) / 2.f;
                float const offset_height = (event.size.height - new_height) / 2.f;

                auto view = window.getDefaultView();
                if (event.size.width >= aspectRatio * event.size.height)
                {
                    view.setViewport(sf::FloatRect(offset_width / event.size.width, 0,
                                                   new_width    / event.size.width, 1));
                }
                else
                {
                    view.setViewport(sf::FloatRect(0, offset_height / event.size.height,
                                                   1, new_height    / event.size.height));
                }
                window.setView(view);
            }
            else
                screen->onEvent(event);
             /*if (event.type == sf::Event::MouseMoved)
            {
                miniMapPosition.setString(fmt::format("\t\t{}/{}", event.mouseMove.x,
                                                                   event.mouseMove.y));
                miniMapPosition.setPosition(
                    miniMapHeaderLabel.getPosition().x + miniMapHeaderLabel.getLocalBounds().width,
                    miniMapHeaderLabel.getPosition().y
                );
            }*/

        }

        screen->update(clock.restart());

        gameTexture.clear(sf::Color::White);
        screen->draw(gameTexture);
        gameTexture.display();

        window.clear();
        window.draw(sf::Sprite(gameTexture.getTexture()));
        window.display();
//        window.draw(header);
//        window.draw(hpAmountBg);
//        window.draw(shieldAmountBg);
//        window.draw(ammoAmountBg);
//        window.draw(rocketAmountBg);
//        window.draw(miniMap);
//        window.draw(miniMapHeader);
//        window.draw(configLabelBg);
//        window.draw(configActive);
//        window.draw(configInactive);
//        window.draw(inventoryRight);
//        window.draw(inventoryCenter);
//        window.draw(inventoryLeft);
//        window.draw(inventoryTriangle);
//        window.draw(inventoryContentBg);
//        // Draw text on top
//        window.draw(miniMapHeaderLabel);
//        window.draw(miniMapPosition);
//        window.draw(configLabel);
//        window.draw(config1);
//        window.draw(config2);
//        window.draw(xpLabel);
//        window.draw(xpValue);
//        window.draw(levelLabel);
//        window.draw(levelValue);
//        window.draw(honorLabel);
//        window.draw(honorValue);
//        window.draw(jackpotLabel);
//        window.draw(jackpotValue);
//        window.draw(creditsLabel);
//        window.draw(creditsValue);
//        window.draw(uridiumLabel);
//        window.draw(uridiumValue);
//        window.draw(cargoLabel);
//        window.draw(cargoValue);
    }
}
catch (std::exception const & e)
{
    spdlog::critical(Core::formatExceptionStack(e));
    return EXIT_FAILURE;
}
