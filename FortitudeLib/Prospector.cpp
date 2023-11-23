#include "include/Prospector.h"


Prospector::Prospector(Attributes attr) : Tower(attr)
{
    _blastRadius = 50;
    _damageDropoffMod = 2;
}


void Prospector::fire()
{
  
    getRecoilAnimation()->activateForward();
    
    std::shared_ptr<SplashProjectile> proj = std::make_shared<SplashProjectile>(getLocation(), getAccuracy(), getProjectileSpeed(), getDamage(), _blastRadius);
    proj->setProjTexture(getProjTexture(), getBulletScale());
    proj->setDropoff(_damageDropoffMod);
    proj->fire(getTarget());
    addProjectile(proj);
    decrementBullet();
  
}

void Prospector::update(double dt)
{
 // sp->update(dt);
  Tower::update(dt);
}

void Prospector::draw(sf::RenderWindow* context)
{
 // sp->draw(context);
  Tower::draw(context);
}
