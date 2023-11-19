#pragma once
#include <SFML/Graphics.hpp>
#include "Tower.h"

class Blaster : public Tower
{
private:
  int _projectileCount;
  std::vector<sf::Vector2f> _mods;
public:
  Blaster(Attributes attr);
  void fire();
};