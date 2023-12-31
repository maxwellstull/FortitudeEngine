#include "include/Marshall.h"


Marshall::Marshall(Attributes attr) : Tower(attr)
{
	_armorPiercing = 0.2; 
}

void Marshall::fire()
{

	getRecoilAnimation()->activateForward();

	double damage = getDamage();

	std::shared_ptr<Projectile> proj = std::make_shared<Projectile>(getLocation(), getAccuracy(), getProjectileSpeed(), damage);
	proj->setProjTexture(getProjTexture(), getBulletScale());
	proj->setArmorPierce(getArmorPierce());
	// Todo: Implement armor piercing once armor is implemented :)

	proj->fire(getTarget());
	addProjectile(proj);
	decrementBullet();
}
