#pragma once
#include <SFML/Graphics.hpp>

class MenuComponent
{
private:
    struct states {
        sf::Vector2f origin;
        sf::Color colour;
        int size;
    };
    sf::Text viewedText;
    int down;
    int up;
    int left;
    int right;
    states onSel;
    states onDesel;

public:
    MenuComponent(const char* label,
        sf::Font * font, sf::Vector2f position, int size);
    void Draw(sf::RenderWindow* context);
    void setControlBind(int upB, int downB, int leftB, int rightB) 
    {
        up = upB; 
        down = downB; 
        left = leftB; 
        right = rightB; }
    void onSelect(sf::Color colour, int size);
    void select();
    void deselect();
    int onDown() { return down; }
    int onUp() { return up; }
    int onLeft() { return left; }
    int onRight() { return right; }
};
