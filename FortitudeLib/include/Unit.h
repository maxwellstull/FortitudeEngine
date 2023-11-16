#pragma once
#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <memory>
#include <cmath>
#include <vector>
#include "GameStructures.h"
#include "Animation.h"

class Unit {
public:
  // Common attributes of a unit
  struct Attributes {
    double maxHealth;
    double health;
    double damage;
    double fireRate;
    double range;
  };

private:
  // Current location of unit
  sf::Vector2f _location;
  // Attributes
  Attributes _attributes;
  // If unit is active ("alive")
  bool _active;
  //Textures, sprites, gun animation info, and health bar
  sf::Texture* _bodyTexture;
  sf::Sprite _bodySpr;
  sf::Texture* _gunTexture;
  sf::Sprite _gunSpr;
  Animation _gunFireAnimation;
  Animation _gunRecoilAnimation;
  sf::RectangleShape _curHealthBar;
  sf::RectangleShape _maxHealthBar;
  bool _healthBar;

  //Generic target
  std::shared_ptr<Unit> target;
  bool validTarget;

public:
  void update(double dt);
  void draw(sf::RenderWindow* context);

  void setBodyTexture(sf::Texture* texture, double scale);
  void setGunTexture(sf::Texture* texture, double scale, sf::Vector2f offset);
  void initialize(bool showHealthBar);
  void findTarget(std::vector<std::shared_ptr<Unit>> ops);
  double getAnimationValue();

  void setAttributes(Attributes attr) { _attributes = attr; }
  Attributes getAttributes() { return _attributes; }
  void setMaxHealth(double hp) { _attributes.maxHealth = hp; }
  void setHealth(double hp) { _attributes.health = hp; }
  void setDamage(double dmg) { _attributes.damage = dmg; }
  void setFireRate(double rt) { _attributes.fireRate = rt; }
  void setRange(double rn) { _attributes.range = rn; }
  double getMaxHealth() { return _attributes.maxHealth; }
  double getHealth() { return _attributes.health; }
  double getDamage() { return _attributes.damage; }
  double getFireRate() { return _attributes.fireRate; }
  double getRange() { return  _attributes.range; }

  double computeDistance(double dx, double dy) { return sqrt(pow(dx, 2) + pow(dy, 2)); }
  bool isActive() { return _active; }
  void activate() { _active = true; }
  void deactivate() { _active = false; }
  sf::Vector2f getLocation() { return _location; }
  void setLocation(sf::Vector2f loc) { _location = loc; }

};