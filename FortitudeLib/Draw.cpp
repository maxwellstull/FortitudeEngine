//#include "stdafx.h"
#include "include/Engine.h"
#include <iostream> 

void Engine::draw()
{
    // Rub out the last frame
    window.clear(sf::Color::White);

    // Draw the background
//    window.draw(m_BackgroundSprite);
//    window.draw(m_Bob.getSprite());
    menu.Draw(window.GetWindow());
//    sf::Font font;
//    if (!font.loadFromFile("img/cowboy.ttf"))
//    {
//        std::cout << "yea it fucked up";
//    }
//    sf::Text texty;
//    texty.setFont(font);
//    texty.setCharacterSize(24);
//    texty.setFillColor(sf::Color::Red);
//    texty.setString("stringy");
//    window.GetWindow()->draw(texty);
    
    
    //std::cout << "Drawed" << std::endl;


    // get the current mouse position in the window
    sf::Vector2i pixelPos = sf::Mouse::getPosition(*window.GetWindow());

    // convert it to world coordinates
    sf::Vector2f worldPos = window.GetWindow()->mapPixelToCoords(pixelPos);
    shape.setPosition(worldPos);
    window.GetWindow()->draw(shape);

    // Show everything we have just drawn
    window.display();
}