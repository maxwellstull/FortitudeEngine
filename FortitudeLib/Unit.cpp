#include "include/Unit.h"
#include <iostream>

Unit::Unit(Attributes attr)
{
  _location = sf::Vector2f(-100, -100);
  _rotation = 0;
  _attributes = attr;
  _active = false;
  _gunRecoilAnimation = Animation(0, 60, 0.05);
  _gunResetAnimation = Animation(60, 0, 0.5);
  _staticGunRotation = 0;
  _healthBar = false;
  _validTarget = false;
  _targetFindTimer = Timer(0.25);
  _fireTimer = Timer(1.f / attr.fireRate);
  gunLeft = false;
}

void Unit::update(double dt)
{
  if(_active)
  {
    _gunRecoilAnimation.update(dt);
    _gunResetAnimation.update(dt);
    _fireTimer.update(dt);
    _targetFindTimer.update(dt);
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
  _attributes.health -= damage;
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
  getTarget()->takeDamage(getDamage());
  if (getTarget()->isActive() == false)
  {
    setIsTargetValid(false);
    _targetFindTimer.clear();
  }
}

void Unit::setLocation(sf::Vector2f loc)
{
  _location = loc;
  _bodySpr.setPosition(loc);
  _gunSpr.setPosition(loc);
  _curHealthBar.setPosition(loc);
  _maxHealthBar.setPosition(loc);
}

void Unit::setGunRotation(double rot, double rotmod) 
{ 
  std::cout << "rot " << rot << std::endl;
 
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