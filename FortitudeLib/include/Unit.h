#pragma once
#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <memory>
#include <cmath>
#include <vector>
#include "GameStructures.h"
#include "Animation.h"
#include "Timer.h"
#include "Projectile.h"


class Unit {
public:
  // Common attributes of a unit
  struct Attributes {
    double maxHealth;
    double health;
    double damage;
    double fireRate;
    double range;
    double accuracy; //between 0 and 100
  };

private:
  // Current location of unit
  sf::Vector2f _location;
  // Heading/rotation of unit
  double _rotation;
  // Attributes
  Attributes _attributes;
  // If unit is active ("alive")
  bool _active;
  //Textures, sprites, gun animation info, and health bar
  sf::Texture* _bodyTexture;
  sf::Sprite _bodySpr;
  sf::Texture* _gunTexture;
  sf::Sprite _gunSpr;
  sf::Texture* _projTexture;
  double _bulletScale;
  bool gunLeft;
  double _staticGunRotation;
  Animation _gunRecoilAnimation;
  Animation _gunResetAnimation;
  sf::RectangleShape _curHealthBar;
  sf::RectangleShape _maxHealthBar;
  bool _healthBar;

  //Generic target
  std::shared_ptr<Unit> _target;
  bool _validTarget;
  Timer _targetFindTimer;
  Timer _fireTimer;
  std::vector<std::shared_ptr<Projectile>> shots;

public:
  Unit(Attributes attr);
  void update(double dt);
  void draw(sf::RenderWindow* context);
  void initialize(bool showHealthBar);

  void setBodyTexture(sf::Texture* texture, double scale);
  sf::Sprite* getBodySprite() { return &_bodySpr; }
  void setGunTexture(sf::Texture* texture, double scale, sf::Vector2f offset);
  sf::Sprite* getGunSprite() { return &_gunSpr; }
  void setProjTexture(sf::Texture* texture, double scale);
  void setGunRotation(double rot, double rotmod);
  double getGunRotation() { return _gunSpr.getRotation(); }
  void setStaticGunRotation(double rot) { _staticGunRotation = rot; }
  double getStaticGunRotation() { return _staticGunRotation; }
  Animation* getRecoilAnimation() { return &_gunRecoilAnimation; }
  Animation* getResetAnimation() { return &_gunResetAnimation; }

  bool getIsTargetValid() { return _validTarget; }
  void setIsTargetValid(bool v) { _validTarget = v; }
  void setTarget(std::shared_ptr<Unit> tar) { _target = tar; }
  std::shared_ptr<Unit> getTarget() { return _target; }
  double getTargetTheta();
  double getTargetDistance();

  double getAnimationValue();
  bool getFireTimerStatus() { return _fireTimer.get(); }
  bool getTargetingTimerStatus() { return _targetFindTimer.get(); }

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
  void setLocation(sf::Vector2f loc);
  void fire();
  void takeDamage(double damage);
};