#pragma once
#include <SFML/Graphics.hpp>
#include "MenuComponent.h"
#include <vector>

class MenuManager
{
private:
    std::vector<MenuComponent> components;
    std::vector<sf::Font> fonts;

public:
    void SelectUp();
    void SelectDown();
    void SelectLeft();
    void SelectRight();
    void init();
    void MainMenu();
    void Draw(sf::RenderWindow * context);
};