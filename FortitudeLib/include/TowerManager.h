#pragma once
#include <SFML/Graphics.hpp>
#include "Tower.h"
#include <vector>
#include <memory>

class Game;

class TowerManager
{
private:
  Game* game;
  std::vector<std::shared_ptr<Tower>> towers;
  std::vector<sf::Texture> textures;
public:
  void update(float dtAsSeconds);
  void initialize();
  void Draw(sf::RenderWindow* context);
  Game* getGame() { return game; }
  void setGame(Game* g) { game = g;}
  std::vector<std::shared_ptr<Tower>> getTowers() { return towers; }
}; 