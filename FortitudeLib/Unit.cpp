#include "include/Unit.h"
#include <iostream>

Unit::Unit(Attributes attr)
{
    double reloadTime = 5;
  _location = sf::Vector2f(-100, -100);
  _rotation = 0;
  _attributes = attr;
  _active = false;
  _gunRecoilAnimation = Animation(0, 60, 0.05);
  _gunResetAnimation = Animation(60, 0, 0.5);
  _staticGunRotation = 0;
  _healthBar = false;
  _validTarget = false;
  _fireTimer = Timer(1.f / attr.fireRate);
  _fireTimer.setReady();
  _targetingTimer = Timer(0.15);
  _targetingTimer.setReady();
  gunLeft = false;
  _deltaPerSec = sf::Vector2f(0, 0);

  _blinded = false;
  


  _reloadAnim = Animation(30, 0, reloadTime);
  _reloadAnim.setOnCompleteFunction([this]() {completeReload(); });

  _reloadBar.setPosition(getLocation());
}

void Unit::update(double dt)
{
  if(_active)
  {
    _gunRecoilAnimation.update(dt);
    _gunResetAnimation.update(dt);
    _fireTimer.update(dt);
    _targetingTimer.update(dt);
    updateReloadAnim(dt);
    for (std::shared_ptr<Projectile> proj : shots)
    {
      proj->update(dt);
    }
    for (auto t : _statusTimers)
    {
        t.update(dt);
    }
    if (isAmmoReloading())
    {
        updateReloadToAnim();
    }
  }
}

void Unit::draw(sf::RenderWindow* context)
{
  if (_active)
  {
    if (_healthBar)
    {
      context->draw(_maxHealthBar);
      context->draw(_curHealthBar);
    }
    context->draw(_bodySpr);
    context->draw(_gunSpr);
    for (auto proj : shots)
    {
      proj->draw(context);
    }
    if (isAmmoReloading())
    {
        drawReloadBar(context);
    }
  }
}

void Unit::setBodyTexture(sf::Texture* texture, double scale)
{
  _bodyTexture = texture;
  _bodySpr.setTexture(*_bodyTexture);
  _bodySpr.setScale(scale, scale);
  sf::FloatRect bds = _bodySpr.getLocalBounds();
  _bodySpr.setOrigin(bds.left + (bds.width / 2.f), bds.top + (bds.height / 2.f));
}

void Unit::setGunTexture(sf::Texture* texture, double scale, sf::Vector2f offset)
{
  _gunTexture = texture;
  _gunSpr.setTexture(*_gunTexture);
  _gunSpr.setScale(scale, scale);
  sf::FloatRect bds = _gunSpr.getLocalBounds();
  _gunSpr.setOrigin(bds.left + (bds.width / 2.f) + offset.x, bds.top + (bds.height / 2.f) + offset.y);
}

void Unit::initialize(bool showHealthBar)
{
  _healthBar = showHealthBar;
  if (_healthBar)
  {
    _maxHealthBar = sf::RectangleShape(sf::Vector2f(30, 5));
    sf::FloatRect bds = _maxHealthBar.getLocalBounds();
    _maxHealthBar.setOrigin(bds.left + (bds.width / 2.f), bds.top + (bds.height / 2.f) - 22);
    _maxHealthBar.setFillColor(sf::Color::Red);

    _curHealthBar = sf::RectangleShape(sf::Vector2f(30, 5));
    bds = _curHealthBar.getLocalBounds();
    _curHealthBar.setOrigin(bds.left + (bds.width / 2.f), bds.top + (bds.height / 2.f) - 22);
    _curHealthBar.setFillColor(sf::Color::Green);

    _maxHealthBar.setPosition(getLocation());
    _curHealthBar.setPosition(getLocation());
  }

  _reloadBar = sf::RectangleShape(sf::Vector2f(30, 5));
  sf::FloatRect bds = _reloadBar.getLocalBounds();
  _reloadBar.setOrigin(bds.left + (bds.width / 2.f), bds.top + (bds.height / 2.f) - 27);
  _reloadBar.setFillColor(sf::Color::Yellow);
  _reloadBar.setSize(sf::Vector2f(0, 5));

  //_gunRecoilAnimation = Animation(0, 45, (1.f / _attributes.fireRate) / 3);
  //_gunResetAnimation = Animation(45, 0, (1.f / _attributes.fireRate) / 2);
  
  _gunRecoilAnimation.setOnCompleteFunction([this]() {this->getResetAnimation()->activateForward(); });
  activate();
}

double Unit::getAnimationValue()
{
  double retVal = 0;
  if (_gunRecoilAnimation.isActive())
  {
    retVal = _gunRecoilAnimation.get();
  }
  else if (_gunResetAnimation.isActive())
  {
    retVal = _gunResetAnimation.get();
  }
  return retVal;
}

void Unit::takeDamage(double damage)
{
  double armor = getArmor();
  double armorPierce = getArmorPierce();

  double absorption = 1.0 - armorPierce;

  
  double armordmg = damage * absorption;
  double healthdmg = damage * armorPierce;
  _attributes.health -= healthdmg;
  _attributes.armor -= armordmg;
  

 
  if(getHealth() > 0)
  {
    double bar = (_maxHealthBar.getSize().x / getMaxHealth()) * getHealth();
    _curHealthBar.setSize(sf::Vector2f(bar, 5));
  }
  else //he died 
  {
    deactivate();
  }
}

void Unit::addHealth(double health)
{
    _attributes.health += health;
    if (getHealth() > getMaxHealth())
    {
        _attributes.health = getMaxHealth();
    }
}

void Unit::addStatusEffect(StatusEffects eft, double duration)
{
    BlindTimer t1 = BlindTimer(duration);
    switch (eft)
    {
    case StatusEffects::BLINDED:
    {
        setBlinded();
        t1.setOnCompleteFunction([this]() {this->clearBlinded(); });
        break;
    }
    case StatusEffects::BLEEDING:
        setBleeding();        
        t1.setOnCompleteFunction([this]() {this->clearBleeding(); });
        break;
    }

    _statusTimers.push_back(t1);
}

double Unit::getTargetTheta()
{
  return atan2(getTarget()->getLocation().y - getLocation().y, getTarget()->getLocation().x - getLocation().x);
}

double Unit::getTargetDistance()
{
  return computeDistance(getTarget()->getLocation().x - getLocation().x, getTarget()->getLocation().y - getLocation().y);
}

void Unit::fire()
{
    _gunRecoilAnimation.activateForward();
    std::shared_ptr<Projectile> proj = std::make_shared<Projectile>(getLocation(), _attributes.accuracy, 1000, _attributes.damage);
    proj->setProjTexture(_projTexture, _bulletScale);
    proj->fire(getTarget());
    shots.push_back(proj);
}

void Unit::setLocation(sf::Vector2f loc)
{
  _location = loc;
  _bodySpr.setPosition(loc);
  _gunSpr.setPosition(loc);
  _curHealthBar.setPosition(loc);
  _maxHealthBar.setPosition(loc);
  _reloadBar.setPosition(loc);
}

void Unit::setProjTexture(sf::Texture* texture, double scale)
{
  _projTexture = texture;
  _bulletScale = scale;
}

void Unit::setGunRotation(double rot, double rotmod)
{  
  if ((rot > 90 || rot < -90) && (gunLeft == false))
  {
    gunLeft = true;
    _gunSpr.scale(-1.f, 1.f);
  }
  else if(rot < 90 && rot > -90 && gunLeft == true)
  {
    gunLeft = false;
    _gunSpr.scale(-1.f, 1.f);
  }
  
  _gunSpr.setRotation(rot + (gunLeft ? 180 + rotmod : -rotmod));
}

void Unit::setRecoilAnimation(double start, double stop, double dur)
{
    _gunRecoilAnimation = Animation(start, stop, dur);
}

void Unit::setResetAnimation(double start, double stop, double dur)
{
    _gunResetAnimation = Animation(start, stop, dur);
}

void Unit::decrementBullet()
{
    _gunAmmo.ammo -= 1;
}

bool Unit::isAmmoEmpty()
{
    if (_gunAmmo.ammo <= 0)
    {
        std::cout << " HEY WE OUT FAM" << std::endl;
        return true;
    }
    else
    {
        return false;
    }
}

bool Unit::isAmmoReloading()
{
    return _reloadAnim.isActive();
}

void Unit::completeReload()
{
    _gunAmmo.ammo = _gunAmmo.maxClip;
}

void Unit::drawReloadBar(sf::RenderWindow* context)
{
    //std::cout << "draw reload bar" << std::endl;
    context->draw(_reloadBar);
}

void Unit::queueReload()
{
    _reloadAnim.activateForward();
}