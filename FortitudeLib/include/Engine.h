#pragma once
#include <SFML/Graphics.hpp>
#include "WindowManager.h"
#include "MenuManager.h"

class Engine
{
private:
    WindowManager window;
    MenuManager menu;
    sf::CircleShape shape;
    sf::Sprite sprite;
    sf::Texture texture;
    // Private functions for internal use only
    void input();
    void update(float dtAsSeconds);
    void draw();

public:
    // The Engine constructor
    Engine();

    // start will call all the private functions
    void GameLoop();

};