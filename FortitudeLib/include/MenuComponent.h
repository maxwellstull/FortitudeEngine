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
//    void SetLocation(double x, double y) { text.setPosition(x, y); }
//    void SetLocation(sf::Vector2i loc) { text.setPosition(loc.x, loc.y); }

};
