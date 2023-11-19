#pragma once
#include <SFML/Graphics.hpp>
#include "Tower.h"

class Blaster : public Tower
{
private:
  int _projectileCount;
public:
  Blaster(Attributes attr);
  void fire();
};