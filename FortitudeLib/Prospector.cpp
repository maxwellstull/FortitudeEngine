#include "include/Prospector.h"


Prospector::Prospector(Attributes attr) : Tower(attr)
{
  _something = false;
}


void Prospector::fire()
{
  
    getRecoilAnimation()->activateForward();
    
    std::shared_ptr<SplashProjectile> proj = std::make_shared<SplashProjectile>(getLocation(), getAccuracy(), getProjectileSpeed(), getDamage(), 100);
    proj->setProjTexture(getProjTexture(), getBulletScale());
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
