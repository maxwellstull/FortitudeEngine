#pragma once
#include <SFML/Graphics.hpp>
#include "MenuManager.h"


class TowerStatMenuManager : public MenuManager
{
private:
  sf::Font fonty;
  std::shared_ptr<sf::Text> _health;
  std::shared_ptr<sf::Text> _damage;
  std::shared_ptr<sf::Text> _range;
  std::shared_ptr<sf::Text> _accuracy;
  std::shared_ptr<sf::Text> _ammo;
  std::shared_ptr<Tower> _splashed;
public:
  void TowerSplash(std::shared_ptr<Tower> theGuy);
  void refresh();
};