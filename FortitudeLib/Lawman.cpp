#include "include/Lawman.h"
#include <cstdlib>


Lawman::Lawman(Attributes attr) : Tower(attr)
{
	_rouletteBulletsPerClip = 1;
	_rouletteDamageIncrease = 1.5;
	_rouletteBulletIdx = (rand() % 6) + 1; //1 thru 6
}

void Lawman::fire()
{
	if (getTarget()->isActive() == false)
	{
		setIsTargetValid(false);
	}
	else
	{
		getRecoilAnimation()->activateForward();

		double damage = getDamage();
		
		std::cout << "lawman shot" << std::endl;
		std::shared_ptr<Projectile> proj = std::make_shared<Projectile>(getLocation(), getAccuracy(), getProjectileSpeed(), damage);
		proj->setProjTexture(getProjTexture(), getBulletScale());
		if (getRemainingBullets() == _rouletteBulletIdx)
		{
			damage = damage * _rouletteDamageIncrease;
			proj->setSpriteColor(sf::Color::Magenta);
			proj->setDamage(damage);
			std::cout << "Shooting out special bullet" << std::endl;
		}
		proj->fire(getTarget());
		addProjectile(proj);
		decrementBullet();

	}
}