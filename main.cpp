#include "main.h"
#include "FortitudeLib/Engine.h"
#include <iostream>

int main()
{
    sf::RenderWindow window;
//    window.create(sf::VideoMode(1920, 1080), "Window", sf::Style::Fullscreen);
    window.create(sf::VideoMode(800, 600), "Window", sf::Style::Default);
    window.setVerticalSyncEnabled(true);
    //window.setFramerateLimit(60);


    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color(100, 250, 50));

    while (window.isOpen())
    {

        sf::Vector2i localpos = sf::Mouse::getPosition(window);
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            //std::cout << "HELLO!";
        }
        window.clear(sf::Color::Black);
        shape.setPosition(localpos.x, localpos.y);

        window.draw(shape);
        




        window.display();
    }

    return 0;
}


/*int main()
{
    // Declare an instance of Engine
    Engine engine;

    // Start the engine
    engine.start();

    // Quit in the usual way when the engine is stopped
    return 0;
}*/