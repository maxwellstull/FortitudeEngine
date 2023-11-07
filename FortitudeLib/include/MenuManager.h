#pragma once
#include <SFML/Graphics.hpp>
#include "MenuComponent.h"
#include "MenuOption.h"
#include <vector>
#include <memory>

class Engine;

class MenuManager
{
private:
    Engine * engine = nullptr;
    std::vector<std::shared_ptr<MenuComponent>> components;
    std::vector<sf::Font> fonts;
    std::shared_ptr<MenuComponent> selected;
    bool active = true;


public:
    void SelectUp();
    void SelectDown();
    void SelectLeft();
    void SelectRight();
    void init();
    void update(float dtAsSeconds);
    void MainMenu();
    void Options();
//    void FullscreenContext();
    void Draw(sf::RenderWindow * context);
    bool isActive() { return active; }
    void SetEngine(Engine* e) { engine = e; }
    Engine* GetEngine() { return engine; }
    void Enter();

};