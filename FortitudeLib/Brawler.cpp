#define _USE_MATH_DEFINES
#include <cmath>
#include "include/Brawler.h"
#include "include/TowerManager.h"
#include "include/Game.h"
#include "include/EnemyManager.h"
#include "include/Enemy.h"

Brawler::Brawler(Attributes attr, sf::Texture * tex, double scale) : Tower(attr)
{
	double meleeSpeed = 1.0;
	setGlassTexture(tex, scale);
	_bleedDuration = 2.0;
	_meleeRange = 200;
	_meleeDamage = 10;
	_meleeTimer = Timer(meleeSpeed);
	_validMeleeTarget = false;

	_meleeSwingAnimation = Animation(0, -60, 0.1);
	_meleeUnswingAnimation = Animation(-60, 0, 0.5);
}

void Brawler::initialize()
{
	_smallRangeCircle = sf::CircleShape(_meleeRange);
	sf::FloatRect bds = _smallRangeCircle.getLocalBounds();
	_smallRangeCircle.setOrigin(bds.left + bds.width / 2.0f, bds.top + bds.height / 2.0f);
	_smallRangeCircle.setPosition(getLocation());
	_smallRangeCircle.setOutlineColor(sf::Color(50, 50, 50));
	_smallRangeCircle.setFillColor(sf::Color::Transparent);
	_smallRangeCircle.setOutlineThickness(4);

	_meleeSwingAnimation.setOnCompleteFunction([this]() {this->getUnswingAnimation()->activateForward(); });
	Tower::initialize();
}

void Brawler::setGlassTexture(sf::Texture* tex, double scale)
{
	_glassTexture = tex;
	_glassScale = scale;
}

double Brawler::getMeleeTargetTheta()
{
	return atan2(_meleeTarget->getLocation().y - getLocation().y, _meleeTarget->getLocation().x - getLocation().x);
}

double Brawler::getMeleeTargetDistance()
{
	return Unit::computeDistance(_meleeTarget->getLocation().x - getLocation().x, _meleeTarget->getLocation().y - getLocation().y);
}

void Brawler::fire()
{
//	getRecoilAnimation()->activateForward();
	_meleeSwingAnimation.activateForward();

	double damage = getDamage();

	std::shared_ptr<Projectile> proj = std::make_shared<Projectile>(getLocation(), getAccuracy(), getProjectileSpeed(), damage);
	proj->setProjTexture(_glassTexture, _glassScale);
	proj->setOnImpactFunction([this]() {this->getTarget()->addStatusEffect(StatusEffects::BLEEDING, this->getBleedDuration()); });
	proj->setSpin(true);
	proj->fire(getTarget());
	addProjectile(proj);
	decrementBullet();
}

void Brawler::update(double dtAsSeconds)
{
	_meleeSwingAnimation.update(dtAsSeconds);
	_meleeUnswingAnimation.update(dtAsSeconds);
	_meleeTimer.update(dtAsSeconds);
	Tower::update(dtAsSeconds);
	if (isActive())
	{
		if (isAmmoReloading())
		{
//			updateReloadToAnim();
			if (_meleeTarget)
			{
				if(_meleeTarget->isActive() == false)
				{
					_validMeleeTarget = false;
				}
			}
			if (_validMeleeTarget == false)
			{
				findMeleeTarget();
				setGunRotation(getStaticGunRotation(), getMeleeAnimationValue());
			}
			if (_validMeleeTarget == true)
			{
				double theta = getMeleeTargetTheta();
				double distance = getMeleeTargetDistance();
				setGunRotation(theta * 180 / M_PI, getMeleeAnimationValue());
				if (distance < _meleeRange)
				{
					if (_meleeTimer.get() == true)
					{
						meleeFire();
					}
				}
				else
				{
					std::cout << " Too far: " << distance << std::endl;
				}
			}
		}
		else
		{
			if(getTarget())
			{
				double theta = getTargetTheta();
				setGunRotation(theta * 180 / M_PI, getMeleeAnimationValue());
			}
		}
	}
}

void Brawler::findMeleeTarget()
{
	double min_distance = INFINITY;
	double distance;
	double theta;
	double xd;
	double yd;
	for (std::shared_ptr<Unit> op : getTowerManager()->getGame()->getEnemyManager()->getEnemies())
	{
		if (op->isActive())
		{
			xd = op->getLocation().x - getLocation().x;
			yd = op->getLocation().y - getLocation().y;
			if (abs(xd) < _meleeRange && abs(yd) < _meleeRange)
			{
				//				theta = atan2(yd, xd);
				//				std::cout << xd << " " << yd << " " << theta << std::endl;
				distance = computeDistance(xd, yd);
				if (distance < _meleeRange && distance < min_distance)
				{
					min_distance = distance;
					_meleeTarget = op;
					_validMeleeTarget = true;
					break; //this affects finding closest
				}
			}
		}
	}
}

void Brawler::drawRangeCircle(sf::RenderWindow* context)
{
//	std::cout << "Draw please " << std::endl;
	context->draw(_smallRangeCircle);
	Tower::drawRangeCircle(context);
}


void Brawler::meleeFire()
{
	std::cout << "SHANK " << std::endl;
	_meleeSwingAnimation.activateForward();
	getTarget()->takeDamage(_meleeDamage);
}

double Brawler::getMeleeAnimationValue()
{
	double retVal = 0;
	if (_meleeSwingAnimation.isActive())
	{
		retVal = _meleeSwingAnimation.get();
	}
	else if (_meleeUnswingAnimation.isActive())
	{
		retVal = _meleeUnswingAnimation.get();
	}
	return retVal;
}

void Brawler::setRangeLocation(sf::Vector2f loc)
{
	_smallRangeCircle.setPosition(loc);
	Tower::setRangeLocation(loc);
}
