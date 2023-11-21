#pragma once
#include <SFML/Graphics.hpp>
#include "Projectile.h"
#include "Animation.h"


class SplashProjectile : public Projectile
{
private:
  bool _something;
  Animation _boom;
  double _radius;
  sf::CircleShape _blast;
public:
  SplashProjectile(sf::Vector2f origin, double accuracy, double speed, double damage, double radius);
  void update(float dt);
  void computeSplash();
  void draw(sf::RenderWindow* context);
  void fire(std::shared_ptr<Unit> target);
  void fire(std::shared_ptr<Unit> target, sf::Vector2f spread);
};