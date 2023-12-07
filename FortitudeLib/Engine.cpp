//#include "stdafx.h"
#include "include/Engine.h"
#include <iostream>

Engine::Engine()
{
    window.init();
    window.SetEngine(this);
    game.SetEngine(this);
    game.setWaveCt(25);
    menu.init();
    menu.SetEngine(this);
    menu.MainMenu();
    leader.init();


    mainScreen = std::make_shared<Map>("img/background.png", "Menu", sf::IntRect(0, 224, 1024, 576));
    mainScreen->setSpriteScale(sf::Vector2f(1.875, 1.875));

    std::shared_ptr<Map> m1 = std::make_shared<Map>("img/map1.png", "Alamo");
    m1->setSpriteScale(sf::Vector2f(2.7, 2.7));
    std::shared_ptr<Map> m2 = std::make_shared<Map>("img/map1.png", "Ol Canteen");
    std::shared_ptr<Map> m3 = std::make_shared<Map>("img/map1.png", "Jail");
    std::shared_ptr<Map> m4 = std::make_shared<Map>("img/map1.png", "Lawman");
    std::shared_ptr<Map> m5 = std::make_shared<Map>("img/map1.png", "Alamo");
    std::shared_ptr<Map> m6 = std::make_shared<Map>("img/map1.png", "Ol Canteen");
    std::shared_ptr<Map> m7 = std::make_shared<Map>("img/map1.png", "Jail");
    
    maps.push_back(m1);
    maps.push_back(m2);
    maps.push_back(m3);
    maps.push_back(m4);
    maps.push_back(m5);
    maps.push_back(m6);
    maps.push_back(m7);

    map = mainScreen;

    fps.init();
//    sf::CircleShape shapey(50);
//    shape = shapey;
//    shape.setFillColor(sf::Color::Blue);
//    shape.setOrigin((shape.getPosition().x / 2.0f) + shape.getRadius(), (shape.getPosition().y / 2.0f) + shape.getRadius());
    texture = sf::Texture();
    texture.loadFromFile("img/background.png", sf::IntRect(0, 224, 1024, 576));

    sprite = sf::Sprite();
    sprite.setTexture(texture);
    sprite.setScale(sf::Vector2f(1.875, 1.875));
}

void Engine::GameLoop()
{
    // Timing
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Time dt = clock.restart();

        // Make a fraction from the delta time
        float dtAsSeconds = dt.asSeconds();
        fps.log(dtAsSeconds);

        input();
        update(dtAsSeconds);
        draw();
        
    }
}
void Engine::setMap(int idx)
{
    map = maps[idx];
    game.setMap(maps[idx]);
    map->initialize();
    //fill out game settings
    GameInfo gameDetails = {

    };
    act = Active::GAME;
    game.load();
}