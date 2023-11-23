#include "include/SplashProjectile.h"
#include "include/Unit.h"
#include <iostream>
SplashProjectile::SplashProjectile(sf::Vector2f origin, double accuracy, double speed, double damage, double radius)
  : Projectile(origin, accuracy, speed, damage)
{
  _radius = radius;
  _boom = Animation(0, 100, 0.25);

  
  _blast.setRadius(10);
  sf::FloatRect bds = _blast.getLocalBounds();
  _blast.setOrigin(bds.left + bds.width / 2.0f, bds.top + bds.height / 2.0f);
  _blast.setOutlineColor(sf::Color::Yellow);
  _blast.setFillColor(sf::Color::Red);
  _blast.setOutlineThickness(10);
  update(0);
}

void SplashProjectile::update(float dt)
{
  if (getActive())
  {
    setLocation(getLocation() + (dt * getDeltaPerSec()));
    double dist = sqrt(pow(getTargetLoc().y - getLocation().y, 2) + pow(getTargetLoc().x - getLocation().x, 2));

    if (!getDespawning() && dist > 5)
    {
      //keep chilling its still in the air
    }
    else
    {
      if (getMiss() == false)
      {
        //splash damage time
        computeSplash();
        deactivate();
        _blast.setPosition(getLocation());
        _boom.activate();
      }
      else //heck we missed
      {
        if (getDespawning())
        {
          getProjSprite()->setColor(sf::Color(255, 255, 255, 255 * (getFadeAway()->get() / 100)));
          getFadeAway()->update(dt);
        }
        else
        {
          setDespawning(true);
          getFadeAway()->activateForward();
        }
      }
    }
  }
  _boom.update(dt);
}

void SplashProjectile::computeSplash()
{
  std::cout << " what the actual heck" << std::endl;
  getTarget()->splashDamageAssist(_radius, getDamage(), getLocation(), getDropoff());
}


void SplashProjectile::draw(sf::RenderWindow* context)
{
  Projectile::draw(context);

  if (_boom.isActive())
  {
    _blast.setRadius(_boom.get());
    sf::FloatRect bds = _blast.getLocalBounds();
    _blast.setOrigin(bds.left + bds.width / 2.0f, bds.top + bds.height / 2.0f);
    context->draw(_blast);
  }
  
}

void SplashProjectile::fire(std::shared_ptr<Unit> target)
{
  _something = false;
  fire(target, sf::Vector2f(0, 0));
}

void SplashProjectile::fire(std::shared_ptr<Unit> target, sf::Vector2f spread)
{
  _something = false;
  Projectile::fire(target, spread);
}
