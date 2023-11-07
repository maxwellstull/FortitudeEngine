//#include "stdafx.h"
#include "include/Engine.h"
#include <iostream>

Engine::Engine()
{
    // Get the screen resolution and create an SFML window and View
//    sf::Vector2f resolution;
//    resolution.x = sf::VideoMode::getDesktopMode().width;
//    resolution.y = sf::VideoMode::getDesktopMode().height;
    window.init();
    window.SetEngine(this);
    menu.init();
    menu.SetEngine(this);
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
//    sprite.setScale(sf::Vector2f(1,1));


//    sf::Texture texturey;
 //   
//    sf::Sprite spritey;
  //  spritey.setTexture(texturey);

//    window.draw(sprite);
    //m_Window.create(VideoMode(resolution.x, resolution.y),
    //    "Simple Game Engine",
    //    Style::Fullscreen);

    // Load the background into the texture
    // Be sure to scale this image to your screen size
    //m_BackgroundTexture.loadFromFile("img/background.jpg");

    // Associate the sprite with the texture
//    m_BackgroundSprite.setTexture(m_BackgroundTexture);

}

void Engine::GameLoop()
{
    // Timing
    sf::Clock clock;

    while (window.isOpen())
    {
       // std::cout << "-= New Loop =-" << std::endl;
        // Restart the clock and save the elapsed time into dt
        sf::Time dt = clock.restart();

        // Make a fraction from the delta time
        float dtAsSeconds = dt.asSeconds();
    //    fps.log(dtAsSeconds);
        float ferps = 1.f / (dtAsSeconds);
       // std::cout << "Alleged: "<<ferps << std::endl;
    //    std::cout << "Calculated:"<<fps.get() << std::endl;
        input();
        update(dtAsSeconds);
        draw();
        
    }
}