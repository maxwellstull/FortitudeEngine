#pragma once
#include <SFML/Graphics.hpp>
#include "WindowManager.h"
#include "MenuManager.h"
#include "FPS.h"
#include "Map.h"
#include "Game.h"
#include "Leaderboard.h"
#include <vector>
#include "GameStructures.h"


class Engine
{
public:
    enum Active
    {
        MENU = 0,
        GAME = 1,
    };
private:
    //Active act;
    WindowManager window;
    MenuManager menu;
    FPS fps;
    Game game;
    Leaderboard leader;
    Active act;

    std::shared_ptr<Map> mainScreen;
    std::shared_ptr<Map> map;
    std::vector<std::shared_ptr<Map>> maps;
    
    sf::Vector2f cursorWorldPos;
//    sf::CircleShape shape;
    sf::Sprite sprite;
    sf::Texture texture;
    // Private functions for internal use only
    void input();
    void update(float dtAsSeconds);
    void draw();
    void hittest(sf::Vector2f cursorPos);

public:
    // The Engine constructor
    Engine();

    // start will call all the private functions
    void GameLoop();

    void close() { window.close(); }
    WindowManager* GetWindowManager() { return &window; }
    FPS* getFps() { return &fps; }
    std::vector<std::shared_ptr<Map>> getMaps() { return maps; }
    sf::Texture* getMapTexture(int idx) { return maps[idx]->getTexture(); }
    std::shared_ptr<Map> getMap(int idx) { return maps[idx]; }
    void setMap(int idx);// { map = maps[idx]; }
    Game* getGame() { return &game; }
    Leaderboard* getLeaderboard() { return &leader; }
};