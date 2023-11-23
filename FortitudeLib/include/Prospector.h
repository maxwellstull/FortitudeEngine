#pragma once
#include <SFML/Graphics.hpp>
#include "SplashProjectile.h"
#include "Tower.h"

class Prospector : public Tower
{
private:
	double _blastRadius;
	double _damageDropoffMod;
public:
  Prospector(Attributes attr);
  void fire();
  void update(double dt);
  void draw(sf::RenderWindow* context);
};