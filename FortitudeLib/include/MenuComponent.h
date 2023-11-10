#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

class MenuComponent
{
public:
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
private:
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
    virtual void Draw(sf::RenderWindow* context);
    void setControlBind(int upB, int downB, int leftB, int rightB) 
    {
        up = upB; 
        down = downB; 
        left = leftB; 
        right = rightB; }
    // Tells what visual changes to do when selected
    void onSelect(sf::Color colour, int size, float duration);
    // Tells object it is selected
    void select();
    // Tells object is is deselected
    void deselect();
    void Update(float dtAsSeconds);
    int onDown() { return down; }
    int onUp() { return up; }
    int onLeft() { return left; }
    int onRight() { return right; }
    // Tells object what to do when pressed enter
    virtual void onEnter(std::function<void()> func);
    // Enter has been pressed
    void enter();

    void setColor(sf::Color c);
    sf::Color getColor() { return viewedText.getFillColor(); }
    animation getAnimation() { return anim; }
    virtual bool hittest(sf::Vector2f cursorPos);


};
