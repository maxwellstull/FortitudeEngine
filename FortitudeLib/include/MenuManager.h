#pragma once
#include <SFML/Graphics.hpp>
#include "MenuComponent.h"
#include <vector>

class Engine;

class MenuManager
{
private:
    Engine * engine = nullptr;
    std::vector<MenuComponent> components;
    std::vector<sf::Font> fonts;
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
    void Options();
    void Draw(sf::RenderWindow * context);
    bool isActive() { return active; }
    void SetEngine(Engine* e) { engine = e; }
};