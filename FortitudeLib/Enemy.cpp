#define _USE_MATH_DEFINES
#include "include/Enemy.h"
#include "include/EnemyManager.h"
#include "include/Path.h"
#include "include/Game.h"
#include "include/Tower.h"
#include <cmath>
#include <iostream>

Enemy::Enemy(Attributes attr) : Unit(attr) 
{
	heading = 0;
}


void Enemy::update(float dtAsSeconds)
{
	Unit::update(dtAsSeconds);
	if (isActive())
	{
//		if (getHealth() <= 0)
//		{
//			deactivate();
//		}

		setLocation(getLocation() + dtAsSeconds * getDeltaPerSec());

		if (destination->contains(getLocation())) //no longer in rectangle - meaning it met the waypoint
		{
			nextDestination();
		}

		if (getIsTargetValid() == false)
		{
			if(getTargetingTimerStatus() == true)
			{
				findTarget();
			}
		}
		else
		{
			double theta = getTargetTheta();
			double distance = getTargetDistance(); 
			if (distance < getRange())
			{
				setGunRotation((theta * 180 / M_PI), getAnimationValue());
				if(isAmmoReloading() == false)
				{
					if (getFireTimerStatus() == true)
					{
						fire();
						if (isAmmoEmpty())
						{
							std::cout << "queueing reload" << std::endl;
							queueReload();
						}
					}
				}
			}
			else
			{
				getGunSprite()->setRotation(0);
				setIsTargetValid(false); //out of range
			}
		}

	}
}

void Enemy::findTarget()
{
	double min_distance = INFINITY;
	double distance;
	double theta;
	double xd;
	double yd;

	for (std::shared_ptr<Unit> op : getEnemyManager()->getGame()->getTowerManager()->getTowers())
	{
		if (op->isActive())
		{
			xd = op->getLocation().x - getLocation().x;
			yd = op->getLocation().y - getLocation().y;
			theta = atan2(yd, xd);

			distance = computeDistance(xd, yd);
			if (distance < getAttributes().range && distance < min_distance)
			{
				min_distance = distance;
				setTarget(op);
				setIsTargetValid(true);
				readyTargetingTimer();
			}
		}
	}
}

void Enemy::draw(sf::RenderWindow* context)
{
	Unit::draw(context);
}


void Enemy::initialize(PathSegment* st)
{
	setLocation(st->getSegmentStart());
	destination = st;
	getBodySprite()->setPosition(getLocation());
	destinationIdx = 0;
	nextDestination();


	getBodySprite()->setColor(sf::Color(50,50,50));

	Unit::initialize(true);
}

void Enemy::nextDestination()
{
	if (destination->getNodeType() == PathNodeType::END) //made it to the end
	{
		deactivate();
		getEnemyManager()->getGame()->decrementCurrentHealth();
	}
	else
	{
		destination->remove(getID());
		destination = destination->getNext();
		destination->add(this);

		double theta = atan2((destination->getSegmentEnd().y - getLocation().y), (destination->getSegmentEnd().x - getLocation().x));
		heading = theta;
		sf::Vector2f delta;
		delta.x = speed * cos(theta);
		delta.y = speed * sin(theta);
		setDeltaPerSec(delta);
	}
}


void Enemy::splashDamageAssist(double rng, double dmg, sf::Vector2f origin, double dropoffCoeff)
{
	std::vector<Enemy *> toCheck;
	for (Enemy* en : destination->getContained())
	{
		toCheck.push_back(en);
	}
	double dist = 0;
	PathSegment* ahead = destination->getNext();
	PathSegment* behind = destination->getPrev();

	while (dist < rng)
	{
		dist += ahead->getLength();

		for (Enemy* en : ahead->getContained())
		{
			toCheck.push_back(en);
		}
		for (Enemy* en : behind->getContained())
		{
			toCheck.push_back(en);
		}

		ahead = ahead->getNext();
		behind = behind->getPrev();
	}

	double appliedDmg;
	for (Enemy* en : toCheck)
	{
		dist = sqrt(pow(en->getLocation().y - origin.y, 2) + pow(en->getLocation().x - origin.x, 2));
		if (dist < rng)
		{
			if (dist < 10)
			{
				appliedDmg = dmg;
			}
			else 
			{
				appliedDmg = dmg / pow(rng / (rng - dist), dropoffCoeff);
			}
			std::cout << "Applied damage: " << appliedDmg << " dist " << dist << std::endl;
			en->takeDamage(appliedDmg);
		}
	}
}


void Enemy::fire()
{
	if (getBlinded() == false)
	{
		Unit::fire();
		decrementBullet();
	}
	else
	{
		std::cout << " I CANT SEE" << std::endl;
	}
}