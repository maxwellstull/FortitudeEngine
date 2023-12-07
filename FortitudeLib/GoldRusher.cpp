#define _USE_MATH_DEFINES
#include <cmath>
#include "include/GoldRusher.h"
#include "include/TowerManager.h"
#include "include/Game.h"
#include "include/EnemyManager.h"
#include "include/Tower.h"

GoldRusher::GoldRusher(Attributes attr) : Enemy(attr)
{
	double meleeSpeed = 1.0;
	_meleeSwingAnimation = Animation(0, -60, 0.1);
	_meleeUnswingAnimation = Animation(-60, 0, 0.5);
}


void GoldRusher::update(float dtAsSeconds)
{
	Enemy::update(dtAsSeconds);
	_meleeSwingAnimation.update(dtAsSeconds);
	_meleeUnswingAnimation.update(dtAsSeconds);
}


void GoldRusher::initialize(PathSegment * st)
{
	_meleeSwingAnimation.setOnCompleteFunction([this]() {this->getUnswingAnimation()->activateForward(); });
	Enemy::initialize(st);
}

double GoldRusher::getMeleeTargetTheta()
{
	return getTargetTheta();
}

double GoldRusher::getMeleeTargetDistance()
{
	return getTargetDistance();
}

void GoldRusher::meleeFire()
{
	_meleeSwingAnimation.activateForward();
	getTarget()->takeDamage(getDamage());
}

void GoldRusher::fire()
{
	meleeFire();
}

double GoldRusher::getMeleeAnimationValue()
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

double GoldRusher::getAnimationValue()
{
	return getMeleeAnimationValue();
}