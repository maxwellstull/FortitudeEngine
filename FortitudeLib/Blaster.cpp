#include "include/Blaster.h"
#include <cstdlib>

Blaster::Blaster(Attributes attr) : Tower(attr)
{
  _projectileCount = 3;

  _mods.clear();

  for (int i = 0; i < _projectileCount; i++)
  {
    _mods.push_back(sf::Vector2f(((rand() % 2 == 0) ? -1 : 1) * (rand() % 10), (((rand() % 2 == 0) ? -1 : 1) * (rand() % 10))));
  }
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
    getRecoilAnimation()->activateForward();
    for(sf::Vector2f mod : _mods)
    {
      std::shared_ptr<Projectile> proj = std::make_shared<Projectile>(getLocation(), getAccuracy(), getProjectileSpeed(), getDamage());
      proj->setProjTexture(getProjTexture(), getBulletScale());
      proj->fire(getTarget(), mod);
      addProjectile(proj);
    }
  }
}