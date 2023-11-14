//#include "stdafx.h"
#include "include/Engine.h"
#include <iostream> 

void Engine::draw()
{
    // Rub out the last frame
    window.clear(sf::Color::White);

    
//    window.GetWindow()->draw(sprite);
    switch(act)
    {
        case Active::MENU:
        {
            map->Draw(window.GetWindow());
            menu.Draw(window.GetWindow());
            break;
        }
        case Active::GAME:
        {
            game.Draw(window.GetWindow());
        }
    }

    fps.Draw(window.GetWindow());

    

    


    // Show everything we have just drawn
    window.display();
}