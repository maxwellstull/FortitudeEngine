#include "include/Doc.h"
#include "include/TowerManager.h"



Doc::Doc(Attributes attr) : Tower(attr)
{
	
}

void Doc::update(double dtAsSeconds)
{
	Tower::update(dtAsSeconds);
}

void Doc::initialize()
{
	setRecoilAnimation(0, -60, 0.1);
	setResetAnimation(-60, 0, 0.5);
	Tower::initialize();
}

void Doc::fire()
{
	getRecoilAnimation()->activateForward();

	getTarget()->takeDamage(getDamage());
	decrementBullet();
}

void Doc::findTarget()
{
	double min_distance = INFINITY;
	double distance;
	double theta;
	double xd;
	double yd;
	for (std::shared_ptr<Unit> op : getTowerManager()->getTowers())
	{
		if (op->isActive())
		{
			if(this != op.get())
			{
				if (op->getHealth() >= op->getMaxHealth())
				{
					xd = op->getLocation().x - getLocation().x;
					yd = op->getLocation().y - getLocation().y;
					if (abs(xd) < getRange() && abs(yd) < getRange())
					{
						distance = computeDistance(xd, yd);
						if (distance < getRange() && distance < min_distance)
						{
							min_distance = distance;
							std::cout << " ITs this guy " << std::endl;
							setTarget(op);
							setIsTargetValid(true);
							break; //this affects finding closest
						}
					}
				}
			}
		}
	}
}