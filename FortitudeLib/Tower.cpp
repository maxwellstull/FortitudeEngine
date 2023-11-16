#define _USE_MATH_DEFINES
#include <cmath>
#include "include/Tower.h"
#include "include/TowerManager.h"
#include "include/Enemy.h"
#include "include/EnemyManager.h"
#include "include/Game.h"
#include <iostream>

Tower::Tower(Attributes attr) : Unit(attr)
{

}

void Tower::initialize()
{
	getBodySprite()->setColor(sf::Color::Magenta);
	Unit::initialize(true);
}


void Tower::update(double dtAsSeconds)
{
	Unit::update(dtAsSeconds);
	if(isActive())
	{
//		if (getHealth() <= 0)
//		{
//			deactivate();
//			std::cout << " deactivate" << std::endl;
//		}
		if (getIsTargetValid() == false)
		{
			findTarget();
		}
		else
		{
			double theta = getTargetTheta();
			double distance = getTargetDistance();
			std::cout << theta << " " << distance << std::endl;
			if (distance < getRange())
			{
				setGunRotation((theta * 180 / M_PI) - getAnimationValue());

				if (getFireTimerStatus() == true)
				{
					fire();
				}
			}
			else
			{
				setIsTargetValid(false); //out of range
			}
		}
	}
}

void Tower::findTarget()
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
			theta = atan2(yd, xd);
			std::cout << xd << " " << yd << " " << theta << std::endl;
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

void Tower::draw(sf::RenderWindow* context)
{
	Unit::draw(context);
}
