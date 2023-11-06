#pragma once
#include <SFML/Graphics.hpp>

class MenuComponent
{
public:
    sf::Text texty;
public:
    MenuComponent(const char* label,
        sf::Font * font, sf::Vector2f position, int size);
    void Draw(sf::RenderWindow* context);
};
