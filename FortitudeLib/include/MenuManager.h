#pragma once
#include <SFML/Graphics.hpp>
#include "MenuComponent.h"
#include "MenuOption.h"
#include "MenuMap.h"
#include <vector>
#include <memory>

class Engine;



class MenuManager
{
public:
    enum inputMethod
    {
        KEYBOARD = 0,
        MOUSE = 1,
    };
private:
    Engine * engine = nullptr;
    std::vector<std::shared_ptr<MenuComponent>> components;
    std::vector<std::shared_ptr<sf::Shape>> shapes;
    std::vector<sf::Font> fonts;
    std::vector<sf::Texture> textures;
    std::shared_ptr<MenuComponent> selected;
    bool active = true;
    inputMethod last_active;

public:
    
    void SelectUp();
    void SelectDown();
    void SelectLeft();
    void SelectRight();
    void init();
    void update(float dtAsSeconds);
    void MainMenu();
    void Options();
    void MapSelect(int page);
//    void MapSelectInit();
//    void FullscreenContext();
    void Draw(sf::RenderWindow * context);
    bool isActive() { return active; }
    void SetEngine(Engine* e) { engine = e; }
    Engine* GetEngine() { return engine; }
    void Enter();
    void deactivate() { active = false; }
    void activate() { active = true; }
    void hitvisit(sf::Vector2f cursorPos);
};