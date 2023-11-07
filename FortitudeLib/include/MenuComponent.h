#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

class MenuComponent
{
private:
    struct states {
        sf::Vector2f origin;
        sf::Color colour;
        int size=0;
    };
    struct animation {
        float start;
        float end;
        float duration;
        float elapsed;
        bool active;
        bool increase;
    };
    sf::Text viewedText;
    int down;
    int up;
    int left;
    int right;
    states onSel;
    states onDesel;
    animation anim;
    std::function<void()> funky;

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
    void onSelect(sf::Color colour, int size, float duration);
    void select();
    void deselect();
    void Update(float dtAsSeconds);
    int onDown() { return down; }
    int onUp() { return up; }
    int onLeft() { return left; }
    int onRight() { return right; }
    void onEnter(std::function<void()> func);
    void enter();
};
