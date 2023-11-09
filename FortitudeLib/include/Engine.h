#pragma once
#include <SFML/Graphics.hpp>
#include "WindowManager.h"
#include "MenuManager.h"
#include "FPS.h"
#include "Map.h"
#include <vector>

enum Active
{
    MENU = 0,
    GAME = 1,
};

class Engine
{
private:
    Active act;
    WindowManager window;
    MenuManager menu;
    FPS fps;
    Map* map;
    std::vector<Map> maps;

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

    void close() { window.close(); }
    WindowManager* GetWindowManager() { return &window; }
    FPS* getFps() { return &fps; }
    std::vector<Map> getMaps() { return maps; }
    sf::Texture* getMapTexture(int idx) { return maps[idx].getTexture(); }
    Map* getMap(int idx) { return &maps[idx]; }
};