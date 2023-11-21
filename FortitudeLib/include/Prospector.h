#pragma once
#include <SFML/Graphics.hpp>
#include "SplashProjectile.h"
#include "Tower.h"

class Prospector : public Tower
{
private:
  bool _something;
  std::shared_ptr<SplashProjectile> sp;
public:
  Prospector(Attributes attr);
  void fire();
  void update(double dt);
  void draw(sf::RenderWindow* context);
};