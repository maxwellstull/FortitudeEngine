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
#include <iostream>

class Unit {
public:
  // Common attributes of a unit
  struct Attributes {
    double health;
    double damage;
    double fireRate;
    double range;
    double accuracy; //between 0 and 100
    double projectileSpeed;
    double armor;
  };
    struct AmmoInfo {
        int ammo;
        double armorPierce;
    };
    struct StatDefaults {
        double maxHealth;
        double maxArmor;
        int maxClip;
    };


private:
  // Current location of unit
  sf::Vector2f _location;
  // Heading/rotation of unit
  double _rotation;
  // Attributes
  Attributes _attributes;
  StatDefaults _defs;
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
  sf::RectangleShape _armorBar;
  bool _healthBar;
  bool _armorVisual;
  sf::Vector2f _deltaPerSec;

  //Generic target
  std::shared_ptr<Unit> _target;
  bool _validTarget;
  Timer _fireTimer;
  std::vector<std::shared_ptr<Projectile>> shots;

  Timer _targetingTimer;

  AmmoInfo _gunAmmo;
  Animation _reloadAnim;
  sf::RectangleShape _reloadBar;

//Status effects
private:
    std::vector<BlindTimer> _statusTimers;
    bool _blinded;
    bool _bleeding;


public:
  Unit(Attributes attr);
  virtual void update(double dt);
  virtual void draw(sf::RenderWindow* context);
  virtual void initialize(bool showHealthBar);

  void setBodyTexture(sf::Texture* texture, double scale);
  sf::Sprite* getBodySprite() { return &_bodySpr; }
  virtual void setGunTexture(sf::Texture* texture, double scale, sf::Vector2f offset);
  sf::Sprite* getGunSprite() { return &_gunSpr; }
  void setProjTexture(sf::Texture* texture, double scale);
  sf::Texture* getProjTexture() { return _projTexture; }
  virtual void setGunRotation(double rot, double rotmod);
  sf::FloatRect getBodyBounds() { return _bodySpr.getLocalBounds(); }
  double getGunRotation() { return _gunSpr.getRotation(); }
  void setStaticGunRotation(double rot) { _staticGunRotation = rot; }
  double getStaticGunRotation() { return _staticGunRotation; }
  Animation* getRecoilAnimation() { return &_gunRecoilAnimation; }
  void setRecoilAnimation(double start, double stop, double dur);
  Animation* getResetAnimation() { return &_gunResetAnimation; }
  void setResetAnimation(double start, double stop, double dur);
  void setDeltaPerSec(sf::Vector2f d) { _deltaPerSec = d; }
  sf::Vector2f getDeltaPerSec() { return _deltaPerSec; }
  double getBulletScale() { return _bulletScale; }
  void addProjectile(std::shared_ptr<Projectile> proj) { shots.push_back(proj); }
  bool getIsTargetValid() { return _validTarget; }
  void setIsTargetValid(bool v) { _validTarget = v; }
  void setTarget(std::shared_ptr<Unit> tar) { _target = tar; }
  std::shared_ptr<Unit> getTarget() { return _target; }
  double getTargetTheta();
  double getTargetDistance();

  virtual void findTarget() = 0;

  virtual double getAnimationValue();
  bool getFireTimerStatus() { return _fireTimer.get(); }
  double DEBUGgetFireTimerStatus() { return _fireTimer.DEBUGget(); }
  bool getTargetingTimerStatus() { return _targetingTimer.get(); }
  void readyTargetingTimer() { _targetingTimer.setReady(); }

  void setAttributes(Attributes attr) { _attributes = attr; }
  Attributes getAttributes() { return _attributes; }
  void setMaxHealth(double hp) { _defs.maxHealth = hp; }
  void setHealth(double hp) { _attributes.health = hp; }
  void setDamage(double dmg) { _attributes.damage = dmg; }
  void setFireRate(double rt) { _attributes.fireRate = rt; }
  void setRange(double rn) { _attributes.range = rn; }
  void setArmor(double ar) { _attributes.armor = ar; }
  double getArmor() { return _attributes.armor; }
  double getMaxHealth() { return _defs.maxHealth; }
  double getHealth() { return _attributes.health; }
  double getDamage() { return _attributes.damage; }
  double getFireRate() { return _attributes.fireRate; }
  double getRange() { return  _attributes.range; }
  double getAccuracy() { return _attributes.accuracy; }
  double getProjectileSpeed() { return _attributes.projectileSpeed; }
  double getArmorPierce() { return _gunAmmo.armorPierce; }
  double getMaxArmor() { return _defs.maxArmor; }

  double computeDistance(double dx, double dy) { return sqrt(pow(dx, 2) + pow(dy, 2)); }
  bool isActive() { return _active; }
  void activate() { _active = true; }
  void deactivate() { _active = false; }
  sf::Vector2f getLocation() { return _location; }
  virtual void setLocation(sf::Vector2f loc);
  virtual void fire();
  void takeDamage(double damage);
  void takeDamage(double damage, double armorPierce);
  void addHealth(double health);
  virtual void splashDamageAssist(double rng, double dmg, sf::Vector2f origin, double dropoffCoeff) { std::cout << "shit" << std::endl; }


  void addStatusEffect(StatusEffects eft, double duration);
  void setBlinded() { _blinded = true; }
  bool getBlinded() { return _blinded; }
  void clearBlinded() { _blinded = false; }
  void setBleeding() { _bleeding = true; }
  bool getBleeding() { return _bleeding; }
  void clearBleeding() { _blinded = false; }
  bool getGunLeft() { return gunLeft; }
  void setGunLeft(bool t) { gunLeft = t; }


  void updateReloadAnim(double dt) { _reloadAnim.update(dt); }
  void updateReloadToAnim() { _reloadBar.setSize(sf::Vector2f(_reloadAnim.get(), 5)); }
  Animation* getReloadAnim() { return &_reloadAnim; }
  void setAmmoInfo(AmmoInfo ami) { _gunAmmo = ami; }
  int getRemainingBullets() { return _gunAmmo.ammo; }
  void decrementBullet();
  bool isAmmoEmpty();
  bool isAmmoReloading();
  virtual void queueReload();
  void drawReloadBar(sf::RenderWindow* context);
  void completeReload();
  int getMaxAmmo() { return _defs.maxClip; }
  void enableArmor() { _armorVisual = true; }
  void drawHealthBar(sf::RenderWindow* context) { context->draw(_maxHealthBar); context->draw(_curHealthBar); }
  void drawArmorBar(sf::RenderWindow* context) { context->draw(_armorBar); }
};