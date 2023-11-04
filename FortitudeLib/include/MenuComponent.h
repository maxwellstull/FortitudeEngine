#pragma once
#include <SFML/Graphics.hpp>

class MenuComponent
{
public:
    sf::Text text;
    sf::Font fonty;
public:
    MenuComponent();
    void Draw(sf::RenderWindow* context);
    void SetLocation(double x, double y) { text.setPosition(x, y); }
    void SetLocation(sf::Vector2i loc) { text.setPosition(loc.x, loc.y); }
    sf::Font getFont() { return fonty; }
};
