#include "include/Blaster.h"


Blaster::Blaster(Attributes attr) : Tower(attr)
{
  _projectileCount = 3;
}


void Blaster::fire()
{
  if (getTarget()->isActive() == false)
  {
    setIsTargetValid(false);
    getTargetFindTimer()->clear();
  }
  else
  {
    std::vector<sf::Vector2f> mods = { sf::Vector2f(15, 10), sf::Vector2f(-10, 5), sf::Vector2f(-10, -3), sf::Vector2f(10, -10) };

    getRecoilAnimation()->activateForward();
    for(sf::Vector2f mod : mods)
    {
      std::shared_ptr<Projectile> proj = std::make_shared<Projectile>(getLocation(), getAccuracy(), getProjectileSpeed(), getDamage());
      proj->setProjTexture(getProjTexture(), getBulletScale());
      proj->fire(getTarget(), mod);
      addProjectile(proj);
    }
  }
}