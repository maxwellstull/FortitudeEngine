#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include <iostream>
#include <functional>

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
  double _armorPierce;
  sf::Vector2f _deltaPerSec;
  double _heading;

  bool _miss;
  bool _active;
  bool _despawning;

  std::function<void()> _onImpact;
  bool _doOnImpact;

  bool _spin;


public:
  Projectile(sf::Vector2f origin, double accuracy, double speed, double damage);
  virtual void update(float dt);
  virtual void draw(sf::RenderWindow* context);
  virtual void fire(std::shared_ptr<Unit> target);
  void fire(std::shared_ptr<Unit> target, sf::Vector2f spread);
  void setProjTexture(sf::Texture* texture, double scale);
  void setSpriteColor(sf::Color c);
  void setArmorPierce(double ap) { _armorPierce = ap; }
  sf::Vector2f getLocation() { return _location; }
  std::shared_ptr<Unit> getTarget() { return _target; }
  void setLocation(sf::Vector2f loc);
  void deactivate() { _active = false; }
  sf::Vector2f getDeltaPerSec() { return _deltaPerSec; }
  bool getActive() { return _active; }
  sf::Vector2f getTargetLoc() { return _targetLoc; }
  bool getDespawning() { return _despawning; }
  void setDespawning(bool st) { _despawning = st; }
  bool getMiss() { return _miss; }
  sf::Sprite* getProjSprite() { return &_projSprite; }
  Animation* getFadeAway() { return &_fadeAway; }
  double getDamage() { return _damage; }
  virtual void computeSplash() { std::cout << "shit mfer" << std::endl; };
  void setDamage(double dmg) { _damage = dmg; }
  void setOnImpactFunction(std::function<void()> func)
  {
	  _onImpact = func;
	  _doOnImpact = true;
  }

  void setSpin(bool t) { _spin = t; }
  bool getSpin() { return _spin; }
};