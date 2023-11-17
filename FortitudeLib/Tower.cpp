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
	_rangeCircle = sf::CircleShape(getRange());
	sf::FloatRect bds = _rangeCircle.getLocalBounds();
	_rangeCircle.setOrigin(bds.left + bds.width / 2.0f, bds.top + bds.height / 2.0f);
	_rangeCircle.setPosition(getLocation());
	_rangeCircle.setOutlineColor(sf::Color(50, 50, 50));
	_rangeCircle.setFillColor(sf::Color::Transparent);
	_rangeCircle.setOutlineThickness(4);

	Unit::initialize(true);
}


void Tower::update(double dtAsSeconds)
{
	Unit::update(dtAsSeconds);
	if(isActive() && _paused == false)
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
				setGunRotation((theta * 180 / M_PI), getAnimationValue());

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
			if(abs(xd) < getAttributes().range && abs(yd) < getAttributes().range)
			{
//				theta = atan2(yd, xd);
//				std::cout << xd << " " << yd << " " << theta << std::endl;
				distance = computeDistance(xd, yd);
				if (distance < getAttributes().range && distance < min_distance)
				{
					min_distance = distance;
					setTarget(op);
					setIsTargetValid(true);
					break;
				}
			}
		}
	}
}

void Tower::draw(sf::RenderWindow* context)
{
	Unit::draw(context);
}

void Tower::drawRangeCircle(sf::RenderWindow* context)
{
	context->draw(_rangeCircle);
}
