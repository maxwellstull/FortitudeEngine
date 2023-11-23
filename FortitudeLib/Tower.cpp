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
	double reloadTime = 5;

	_drawRange = false;
	_reloadAnim = Animation(30, 0, reloadTime);
	_reloadAnim.setOnCompleteFunction([this]() {completeReload(); });
	

	_reloadBar.setPosition(getLocation());
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

	_reloadBar = sf::RectangleShape(sf::Vector2f(30, 5));
	bds = _reloadBar.getLocalBounds();
	_reloadBar.setOrigin(bds.left + (bds.width / 2.f), bds.top + (bds.height / 2.f) - 27);
	_reloadBar.setFillColor(sf::Color::Yellow);
	_reloadBar.setSize(sf::Vector2f(0, 5));
	Unit::initialize(true);
}

std::string trimDoubleToString(double num)
{
	return std::to_string(num).substr(0, std::to_string(num).find(".") + 2);
}
std::string Tower::getHealthString()
{
	return "Hp: " + trimDoubleToString(getHealth()) + "/" + trimDoubleToString(getMaxHealth());
}

std::string Tower::getDamageString()
{
	return "Dmg: " + trimDoubleToString(getDamage() * getFireRate()) + "dps (" + trimDoubleToString(getDamage()) + ", " + trimDoubleToString(getFireRate()) + "/sec";
}

std::string Tower::getRangeString()
{
	return "Rng: " + trimDoubleToString(getRange());
}

std::string Tower::getAccuracyString()
{
	return "Acc: " + trimDoubleToString(getAccuracy());
}

void Tower::decrementBullet()
{
	_gunAmmo.ammo -= 1;
}

bool Tower::isAmmoEmpty()
{
	if (_gunAmmo.ammo <= 0)
	{
		std::cout << " HEY WE OUT FAM" << std::endl;
		return true;
	}
	else
	{
		return false;
	}
}

bool Tower::isAmmoReloading()
{
	return _reloadAnim.isActive();
}


void Tower::update(double dtAsSeconds)
{
	Unit::update(dtAsSeconds);
	_reloadAnim.update(dtAsSeconds);
	if (isActive() && _paused == false)
	{
		//		if (getHealth() <= 0)
		//		{
		//			deactivate();
		//			std::cout << " deactivate" << std::endl;
		//		}
		if (getIsTargetValid() == false)
		{
			if (getTargetingTimerStatus())
			{
				findTarget();
			}
			setGunRotation(getStaticGunRotation(), getAnimationValue());
		}
		else
		{
			if (getIsTargetValid())
			{
				double theta = getTargetTheta();
				double distance = getTargetDistance();
				//std::cout << theta << " " << distance << std::endl;
				if (distance < getRange())
				{
					setGunRotation((theta * 180 / M_PI), getAnimationValue());
					if(isAmmoReloading() == false)
					{
						if (getFireTimerStatus() == true)
						{
							fire();
							setStaticGunRotation((theta * 180 / M_PI));

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
					setIsTargetValid(false); //out of range
				}
			}
		}
		if (isAmmoReloading())
		{
			_reloadBar.setSize(sf::Vector2f(_reloadAnim.get(), 5));
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

bool Tower::hittest(sf::Vector2f cursorPos)
{
	sf::FloatRect bodybounds = getBodySprite()->getGlobalBounds();
	return bodybounds.contains(cursorPos);
}

void Tower::draw(sf::RenderWindow* context)
{
	if (_drawRange)
	{
		drawRangeCircle(context);
	}
//	if (isAmmoReloading())
//	{
		drawReloadBar(context);
//	}
	Unit::draw(context);
}

void Tower::drawRangeCircle(sf::RenderWindow* context)
{
	context->draw(_rangeCircle);
}


void Tower::queueReload()
{
	_reloadAnim.activateForward();
}

void Tower::drawReloadBar(sf::RenderWindow* context)
{
	//std::cout << "draw reload bar" << std::endl;
	context->draw(_reloadBar);
}

void Tower::setLocation(sf::Vector2f loc)
{
	_reloadBar.setPosition(loc);
	Unit::setLocation(loc);
}

void Tower::completeReload()
{
	_gunAmmo.ammo = _gunAmmo.maxClip;
}