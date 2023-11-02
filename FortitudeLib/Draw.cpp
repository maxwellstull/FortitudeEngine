//#include "stdafx.h"
#include "include/Engine.h"

void Engine::draw()
{
    // Rub out the last frame
    window.clear(sf::Color::White);

    // Draw the background
//    window.draw(m_BackgroundSprite);
//    window.draw(m_Bob.getSprite());

    // Show everything we have just drawn
    window.display();
}