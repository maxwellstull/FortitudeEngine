#pragma once
#include <SFML/Graphics.hpp>
#include "Tower.h"
#include <vector>
#include <memory>
#include "Unit.h"
#include "TowerStatMenuManager.h"

class Game;

class TowerManager
{
private:
  Game* game;
  std::vector<std::shared_ptr<Tower>> towers;
  std::vector<sf::Texture> textures;
  TowerStatMenuManager selectedSplash;
  bool splashActive;
  std::shared_ptr<Tower> splashedTower;
  std::shared_ptr<Tower> grabbed;
  bool isGrabbed;
public:
  void update(float dtAsSeconds);
  void initialize();
  void Draw(sf::RenderWindow* context);
  Game* getGame() { return game; }
  void setGame(Game* g) { game = g;}
  std::vector<std::shared_ptr<Tower>> getTowers() { return towers; }
  sf::Texture* getTowerTexture(int idx) { return &textures[idx]; }
  void spawnLawman();
  void spawnMarshall();
  void spawnRepeater();
  void spawnProspector();
  void spawnBlaster();
  void spawnBrawler();
  void release() { isGrabbed = false; grabbed->unpause(); grabbed->clearDrawRange();  towers.push_back(grabbed); }
  void hitvisit(sf::Vector2f cursorPos);
}; 