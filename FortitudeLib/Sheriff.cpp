#define _USE_MATH_DEFINES
#include <cmath>
#include "include/Sheriff.h"
#include "include/TowerManager.h"
Sheriff::Sheriff(Attributes attr) : Tower(attr)
{
  _2ndGunRecoilAnimation = Animation(0, 60, 0.05);
  _2ndGunResetAnimation = Animation(60, 0, 0.5);
  _2ndGunFireTimer = Timer(1.f / attr.fireRate);
  _ammoCap = 6;
  _2ndGunLeft = false;
}

void Sheriff::initialize()
{
  _2ndGunRecoilAnimation.setOnCompleteFunction([this]() {this->get2ndResetAnimation()->activateForward(); });
  _2ndGunFireTimer.update((1.f / getFireRate()) / 2.0f);
  getReloadAnim()->setOnCompleteFunction([this]() {this->Offset2ndGunTimer(); completeReload(); });
  Tower::initialize();
}

void Sheriff::update(double dtAsSeconds)
{
  Tower::update(dtAsSeconds);
  _2ndGunRecoilAnimation.update(dtAsSeconds);
  _2ndGunResetAnimation.update(dtAsSeconds);
  _2ndGunFireTimer.update(dtAsSeconds);

  if (isActive() && isPaused() == false)
  {
    if (getIsTargetValid() == true)
    {
      double theta = getTargetTheta();
      double distance = getTargetDistance();
      //std::cout << theta << " " << distance << std::endl;
      if (distance < getRange())
      {
        set2ndGunRotation((theta * 180 / M_PI), get2ndAnimationValue());
        if (isAmmoReloading() == false)
        {
          if (_2ndGunFireTimer.get() == true)
          {
            otherFire();
            setStaticGunRotation((theta * 180 / M_PI));

            if (isAmmoEmpty())
            {
              queueReload();
            }
          }
          else
          {
            //	std::cout << "fire timer not ready need more seconds: "<<DEBUGgetFireTimerStatus() << std::endl;
          }
        }
        else
        {
          //	std::cout << "da ammo is reloading need moor boolets" << std::endl;
        }
      }
      else
      {
        setIsTargetValid(false); //out of range
      }
    }
    else
    {

    }
  }
}

void Sheriff::fire()
{
  getRecoilAnimation()->activateForward();
  std::shared_ptr<Projectile> proj = std::make_shared<Projectile>(getLocation(), getAccuracy(), getProjectileSpeed(), getDamage());
  proj->setProjTexture(getProjTexture(), getBulletScale());
  proj->fire(getTarget());
  addProjectile(proj);
  decrementBullet();
}

void Sheriff::otherFire()
{
  _2ndGunRecoilAnimation.activateForward();
  std::shared_ptr<Projectile> proj = std::make_shared<Projectile>(getLocation(), getAccuracy(), getProjectileSpeed(), getDamage());
  proj->setProjTexture(getProjTexture(), getBulletScale());
  proj->fire(getTarget());
  addProjectile(proj);
  decrementBullet();
}

void Sheriff::draw(sf::RenderWindow* context)
{
  Tower::draw(context);
  if (isActive())
  {
    context->draw(_2ndGunSpr);
  }
  
}

void Sheriff::setLocation(sf::Vector2f loc)
{
  _2ndGunSpr.setPosition(loc);
  Tower::setLocation(loc);
}

void Sheriff::setGunTexture(sf::Texture* texture, double scale, sf::Vector2f offset)
{
  _2ndGunTex = texture;
  _2ndGunSpr.setTexture(*_2ndGunTex);
  _2ndGunSpr.setScale(scale, scale);
  sf::FloatRect bds = _2ndGunSpr.getLocalBounds();
  _2ndGunSpr.setOrigin(bds.left + (bds.width / 2.f) + offset.x+50, bds.top + (bds.height / 2.f) + offset.y);
  Tower::setGunTexture(texture, scale, offset);
}

double Sheriff::get2ndAnimationValue()
{
  double retVal = 0;
  if (_2ndGunRecoilAnimation.isActive())
  {
    retVal = _2ndGunRecoilAnimation.get();
  }
  else if (_2ndGunResetAnimation.isActive())
  {
    retVal = _2ndGunResetAnimation.get();
  }
  return retVal;
}

void Sheriff::set2ndGunRotation(double rot, double rotmod)
{
  if ((rot > 90 || rot < -90) && (_2ndGunLeft == false))
  {
    _2ndGunLeft = true;
    _2ndGunSpr.scale(-1.f, 1.f);
  }
  else if (rot < 90 && rot > -90 && _2ndGunLeft == true)
  {
    _2ndGunLeft = false;
    _2ndGunSpr.scale(-1.f, 1.f);
  }

  _2ndGunSpr.setRotation(rot + (_2ndGunLeft ? 180 + rotmod : -rotmod));
}

void Sheriff::Offset2ndGunTimer()
{
  _2ndGunFireTimer.clear();
  _2ndGunFireTimer.update((1.f / getFireRate()) / 2.0f);
}
