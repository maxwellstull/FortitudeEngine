//#include "stdafx.h"
#include "include/Engine.h"
#include <iostream>

void Engine::input()
{
    sf::Vector2i pixelPos = sf::Mouse::getPosition(*window.GetWindow());
    cursorWorldPos = window.GetWindow()->mapPixelToCoords(pixelPos);
    
    hittest(cursorWorldPos);

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
                        break;
                    }
                    case(sf::Keyboard::Down):
                    {
                        menu.SelectDown();
                        break;
                    }
                    case(sf::Keyboard::Right):
                    {
                        menu.SelectRight();
                        break;
                    }
                    case(sf::Keyboard::Left):
                    {
                        menu.SelectLeft();
                        break;
                    }
                    case(sf::Keyboard::Enter):
                    {
                        menu.Enter();
                        break;
                    }
                }
            }
        case sf::Event::MouseButtonPressed:
        {
            switch (event.mouseButton.button)
            {
                case(sf::Mouse::Left):
                {
                    if (menu.isActive())
                    {
                        menu.Enter();
                        break;
                    }
                }
            }
            break;
        }
        }
    }
}

void Engine::hittest(sf::Vector2f cursorPos)
{
    menu.hitvisit(cursorPos);
}