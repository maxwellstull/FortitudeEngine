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

		setLocation(getLocation() + dtAsSeconds * deltaPerSec);

		if (destination->contains(getLocation())) //no longer in rectangle - meaning it met the waypoint
		{
			nextDestination();
		}

		if (getIsTargetValid() == false)
		{
			findTarget();
		}
		else
		{
			double theta = getTargetTheta();
			double distance = getTargetDistance(); 
			if (distance < getRange())
			{
				setGunRotation((theta * 180 / M_PI), getAnimationValue());
				if (getFireTimerStatus() == true)
				{
					fire();
				}
			}
			else
			{
				getGunSprite()->setRotation(0);
				setIsTargetValid(false); //out of range
			}
		}

		
		std::cout << "Health: " << getHealth() << std::endl;
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
	destination = destination->getNext();
	if (destination->getNodeType() == PathNodeType::END) //made it to the end
	{
		deactivate();
		getEnemyManager()->getGame()->decrementCurrentHealth();
	}

	double theta = atan2((destination->getSegmentEnd().y - getLocation().y), (destination->getSegmentEnd().x - getLocation().x));
	heading = theta;
	deltaPerSec.x = speed * cos(theta);
	deltaPerSec.y = speed * sin(theta);
}





