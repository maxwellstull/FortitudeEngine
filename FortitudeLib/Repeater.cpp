#include "include/Repeater.h"

Repeater::Repeater(Attributes attr, sf::Texture * tex, double scale) : Tower(attr)
{
	setPocketSandTexture(tex, scale);
	_pocketSandBlindDuration = 2.0;
}

void Repeater::fire()
{
	if (getTarget()->isActive() == false)
	{
		setIsTargetValid(false);
	}
	else
	{
		getRecoilAnimation()->activateForward();

		double damage = getDamage();

		std::shared_ptr<Projectile> proj = std::make_shared<Projectile>(getLocation(), getAccuracy(), getProjectileSpeed(), damage);
		proj->setProjTexture(getProjTexture(), getBulletScale());
		proj->fire(getTarget());
		addProjectile(proj);
		decrementBullet();
	}
}

void Repeater::queueReload()
{
	Tower::queueReload();
	std::shared_ptr<Projectile> proj = std::make_shared<Projectile>(getLocation(), getAccuracy(), getProjectileSpeed(), 0);
	proj->setProjTexture(_pocketSandTexture, _pocketSandScale);
	proj->setOnImpactFunction([this]() {this->getTarget()->addStatusEffect(StatusEffects::BLINDED, this->getPocketSandDuration()); });
	proj->fire(getTarget());
	addProjectile(proj);

}

void Repeater::setPocketSandTexture(sf::Texture* tex, double scale)
{
	_pocketSandTexture = tex;
	_pocketSandScale = scale;
}
