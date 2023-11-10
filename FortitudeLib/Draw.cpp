//#include "stdafx.h"
#include "include/Engine.h"
#include <iostream> 

void Engine::draw()
{
    // Rub out the last frame
    window.clear(sf::Color::White);

    
//    window.GetWindow()->draw(sprite);
    map->Draw(window.GetWindow());
    fps.Draw(window.GetWindow());

    menu.Draw(window.GetWindow());

    
    

    

//    window.GetWindow()->draw(shape);

    // Show everything we have just drawn
    window.display();
}