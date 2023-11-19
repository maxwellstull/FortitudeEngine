#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Unit;

class Projectile
{
private:
  sf::Texture* _projTexture;
  sf::Sprite _projSprite;

  sf::Vector2f _location;
  sf::Vector2f _origin;
  sf::Vector2f _targetLoc;
  Animation _fadeAway;

  std::shared_ptr<Unit> _target;

  double _speed;
  double _damage;
  sf::Vector2f _deltaPerSec;
  double _heading;

  bool _miss;
  bool _active;
  bool _despawning;



public:
  Projectile(sf::Vector2f origin, double accuracy, double speed, double damage);
  void update(float dt);
  void draw(sf::RenderWindow* context);
  void fire(std::shared_ptr<Unit> target);
  void fire(std::shared_ptr<Unit> target, sf::Vector2f spread);
  void setProjTexture(sf::Texture* texture, double scale);
  sf::Vector2f getLocation() { return _location; }
  void setLocation(sf::Vector2f loc);
  void deactivate() { _active = false; }
};