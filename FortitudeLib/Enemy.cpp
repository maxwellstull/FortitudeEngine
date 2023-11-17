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
//		getBodySprite()->setPosition(getLocation());
//		getGunSprite()->setPosition(getLocation());

		if (!pathingBounds.contains(getLocation())) //no longer in rectangle - meaning it met the waypoint
		{
			newDestination(enm->getGame()->getMap()->getPath()->getNextDestination(++destinationIdx));
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


void Enemy::initialize(std::shared_ptr<PathNode> start_node)
{
	setLocation(start_node->location);
	destination = start_node;
	getBodySprite()->setPosition(getLocation());
	destinationIdx = 0;
	newDestination(getEnemyManager()->getGame()->getMap()->getPath()->getNextDestination(++destinationIdx));

	//temporary
	setMaxHealth(100);
	setHealth(100);
	setDamage(10);
	setFireRate(0.5);
	setRange(300);

	getBodySprite()->setColor(sf::Color(50,50,50));

	Unit::initialize(true);
}

void Enemy::newDestination(std::shared_ptr<PathNode> newD)
{
	if (newD->nodeType == PathNodeType::END)
	{
		deactivate();
		getEnemyManager()->getGame()->decrementCurrentHealth();
	}

	float theta = atan2((newD->location.y - getLocation().y), (newD->location.x - getLocation().x));
	heading = theta;
	deltaPerSec.x = speed * cos(theta);
	deltaPerSec.y = speed * sin(theta);

//	std::cout <<theta<<" " << deltaPerSec.x << " " << deltaPerSec.y << std::endl;

	lastDestination = destination;
	destination = newD;

	pathingBounds = sf::FloatRect(sf::Vector2f
		(destination->location.x < getLocation().x ? destination->location.x - 1: getLocation().x - 1,
		 destination->location.y < getLocation().y ? destination->location.y - 1: getLocation().y - 1),
		sf::Vector2f(
			abs(getLocation().x - destination->location.x) + 1,
			abs(getLocation().y - destination->location.y) + 2));
}





