#pragma once
#include <SFML/Graphics.hpp>
#include "MenuComponent.h"
#include <vector>

class Menu
{
private:
    std::vector<MenuComponent> components;
    MenuComponent* highlighted;

public:
    void SelectUp();
    void SelectDown();
    void SelectLeft();
    void SelectRight();

    void Draw();
};