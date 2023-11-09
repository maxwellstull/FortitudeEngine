//#include "stdafx.h"
#include "include/Engine.h"
#include <iostream>

Engine::Engine()
{
    window.init();
    window.SetEngine(this);
    menu.init();
    menu.SetEngine(this);
    act = Active::MENU;
//    map.init("img/map1.png");

    std::shared_ptr<Map> m1 = std::make_shared<Map>("img/map1.png", "Alamo");
    std::shared_ptr<Map> m2 = std::make_shared<Map>("img/map1.png", "Ol Canteen");
    std::shared_ptr<Map> m3 = std::make_shared<Map>("img/map1.png", "Jail");
    std::shared_ptr<Map> m4 = std::make_shared<Map>("img/map1.png", "Lawman");

    maps.push_back(m1);
    maps.push_back(m2);
    maps.push_back(m3);
    maps.push_back(m4);

    fps.init();
    sf::CircleShape shapey(50);
    shape = shapey;
    shape.setFillColor(sf::Color::Blue);
    shape.setOrigin((shape.getPosition().x / 2.0f) + shape.getRadius(), (shape.getPosition().y / 2.0f) + shape.getRadius());
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