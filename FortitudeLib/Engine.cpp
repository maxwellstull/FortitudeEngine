//#include "stdafx.h"
#include "include/Engine.h"

Engine::Engine()
{
    // Get the screen resolution and create an SFML window and View
//    sf::Vector2f resolution;
//    resolution.x = sf::VideoMode::getDesktopMode().width;
//    resolution.y = sf::VideoMode::getDesktopMode().height;
    window.init();
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
        // Restart the clock and save the elapsed time into dt
        sf::Time dt = clock.restart();

        // Make a fraction from the delta time
        float dtAsSeconds = dt.asSeconds();

        input();
        update(dtAsSeconds);
        draw();
    }
}