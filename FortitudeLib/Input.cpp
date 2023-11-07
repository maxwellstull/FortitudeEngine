//#include "stdafx.h"
#include "include/Engine.h"
#include <iostream>

void Engine::input()
{
    sf::Event event;
    while (window.GetWindow()->pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::Closed:
            {
                window.close();
                break;
            }
        case sf::Event::Resized:
        {
            std::cout << event.size.width << " " << event.size.height << std::endl;
            //window.GetWindow()->setView(sf::View(window.GetWindow()->getView().getCenter(), sf::Vector2f(event.size.width, event.size.height)));
            break;
        }
        case sf::Event::LostFocus:
        {
            window.clearFocus();
            std::cout << "Lost focus" << std::endl;
            break;
        }
        case sf::Event::GainedFocus:
        {
            window.setFocus();
            std::cout << "Gained focus" << std::endl;
            break;
        }
        case sf::Event::KeyPressed:
            if (menu.isActive())
            {
                switch (event.key.code)
                {
                    case(sf::Keyboard::Up):
                    {
                        menu.SelectUp();
                        std::cout << "up";
                        break;
                    }
                    case(sf::Keyboard::Down):
                    {
                        menu.SelectDown();
                        std::cout << "down";
                        break;
                    }
                    case(sf::Keyboard::Enter):
                    {
                        menu.Enter();
                    }
                }
            }
        }
    }
}