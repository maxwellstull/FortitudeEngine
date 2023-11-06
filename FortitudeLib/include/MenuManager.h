#pragma once
#include <SFML/Graphics.hpp>
#include "MenuComponent.h"
#include <vector>

class MenuManager
{
private:
    std::vector<MenuComponent> components;
    std::vector<sf::Font> fonts;
//    int selected = 0;
    MenuComponent* selected;
    bool active = true;

public:
    void SelectUp();
    void SelectDown();
    void SelectLeft();
    void SelectRight();
    void init();
    void update();
    void MainMenu();
    void Draw(sf::RenderWindow * context);
    bool isActive() { return active; }
};