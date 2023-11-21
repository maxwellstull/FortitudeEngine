#include "include/Projectile.h"
#include <cstdlib>
#include "include/Unit.h"

Projectile::Projectile(sf::Vector2f origin, double accuracy, double speed, double damage)
{
  double roll = (rand() % 100) + 1;
  if (roll < accuracy)
  {
    _miss = false;
  }
  else
  {
    _miss = true;
  }
  _location = origin;
  _origin = origin;
  _speed = speed;
  _active = false;
  _damage = damage;
  _heading = 0;
  _despawning = false;
  _fadeAway = Animation(100, 0, 0.2);
  _fadeAway.setOnCompleteFunction([this]() {this->deactivate(); });
}

bool between(sf::Vector2f end1, sf::Vector2f monkey, sf::Vector2f end2)
{
  //check x
  bool retVal = true;
  if (end1.x > end2.x)
  {
    if (end1.x > monkey.x && monkey.x > end2.x)
    {
      retVal = retVal & true;
    }
    else 
    {
      retVal = retVal & false;
    }
  }
  else if (end1.x < end2.x)
  {
    if (end1.x < monkey.x && monkey.x < end2.x)
    {
      retVal = retVal & true;
    }
    else
    {
      retVal = retVal & false;
    }
  }
  if (end1.y > end2.y)
  {
    if (end1.y > monkey.y && monkey.y > end2.y)
    {
      retVal = retVal & true;
    }
    else
    {
      retVal = retVal & false;
    }
  }
  else if (end1.y < end2.y)
  {
    if (end1.y < monkey.y && monkey.y < end2.y)
    {
      retVal = retVal & true;
    }
    else
    {
      retVal = retVal & false;
    }
  }
  return retVal;
}


void Projectile::update(float dt)
{
  if(_active)
  {
    setLocation(getLocation() + (dt * _deltaPerSec));
    double dist = sqrt(pow(_targetLoc.y - getLocation().y, 2) + pow(_targetLoc.x - getLocation().x, 2));
    
    if (!_despawning && (dist > (_target->getBodyBounds().width / 3) || dist > (_target->getBodyBounds().height / 3)))
    {
      //vibe
    }
    else //no longer between
    {
      if (_miss == false)
      {
        _target->takeDamage(_damage);
        deactivate();
      }
      else
      {
        if (_despawning)
        {
          _projSprite.setColor(sf::Color(255, 255, 255, 255 * (_fadeAway.get() / 100)));
          _fadeAway.update(dt);
        }
        else
        {
          _despawning = true;
          _fadeAway.activateForward();
        }
      }
    }
  }
}

void Projectile::setLocation(sf::Vector2f loc)
{
  _location = loc;
  _projSprite.setPosition(loc);
}

void Projectile::draw(sf::RenderWindow* context)
{
  if(_active)
  {
    context->draw(_projSprite);
  }
}

void Projectile::fire(std::shared_ptr<Unit> target)
{
  fire(target, sf::Vector2f(0, 0));
}

void Projectile::fire(std::shared_ptr<Unit> target, sf::Vector2f spread)
{
  double distance = sqrt(pow(target->getLocation().y + spread.y - _location.y, 2) + pow(target->getLocation().x + spread.x - _location.x, 2));
  double travelTime = distance / _speed;
  sf::Vector2f leadingTarget = (target->getLocation() + spread) + sf::Vector2f(target->getDeltaPerSec().x * travelTime, target->getDeltaPerSec().y * travelTime);

  double theta = atan2(leadingTarget.y - _location.y, leadingTarget.x - _location.x);
  _deltaPerSec.x = _speed * cos(theta);
  _deltaPerSec.y = _speed * sin(theta);

  _projSprite.setRotation(theta);

  _targetLoc = leadingTarget;
  _target = target;
  _active = true;
}

void Projectile::setProjTexture(sf::Texture* texture, double scale)
{
  _projTexture = texture;
  _projSprite.setTexture(*_projTexture);
  _projSprite.setScale(scale, scale);
  sf::FloatRect bds = _projSprite.getLocalBounds();
  _projSprite.setOrigin(bds.left + (bds.width / 2.f), bds.top + (bds.height / 2.f));
  setLocation(_location);
}
