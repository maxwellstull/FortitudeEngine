//#include "stdafx.h"
#include "include/Engine.h"
#include <iostream> 

void Engine::draw()
{
    // Rub out the last frame
    window.clear(sf::Color::White);

    
    window.GetWindow()->draw(sprite);

    menu.Draw(window.GetWindow());
    fps.Draw(window.GetWindow());

    sf::Vector2i pixelPos = sf::Mouse::getPosition(*window.GetWindow());
    sf::Vector2f worldPos = window.GetWindow()->mapPixelToCoords(pixelPos);
    shape.setPosition(worldPos);
    window.GetWindow()->draw(shape);

    // Show everything we have just drawn
    window.display();
}