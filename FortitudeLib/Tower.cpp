#define _USE_MATH_DEFINES
#include <cmath>
#include "include/Tower.h"
#include "include/TowerManager.h"
#include "include/Enemy.h"
#include "include/EnemyManager.h"
#include "include/Game.h"

double pythag2(double x, double y)
{
	return sqrt(pow(x, 2) + pow(y, 2));
}

void Tower::initialize()
{
	spr.setColor(sf::Color::Magenta);
	healthRed = sf::RectangleShape(sf::Vector2f(30, 5));
	sf::FloatRect bds = healthRed.getLocalBounds();
	healthRed.setOrigin(bds.left + (bds.width / 2.f), bds.top + (bds.height / 2.f));
	healthRed.setFillColor(sf::Color::Red);

	healthGreen = sf::RectangleShape(sf::Vector2f(30, 5));
	bds = healthGreen.getLocalBounds();
	healthGreen.setOrigin(bds.left + (bds.width / 2.f), bds.top + (bds.height / 2.f));
	healthGreen.setFillColor(sf::Color::Green);

	healthRed.setPosition(location + sf::Vector2f(0, 25));
	healthGreen.setPosition(location + sf::Vector2f(0, 25));

	towerRange = 500;

	fireTimer = 0;
	flashTime = 0.25;
	flashTimeCtr = flashTime;
	activate();
}

void Tower::update(double dtAsSeconds)
{
	if (validTarget == false)
	{
		findTarget();
	}
	else
	{
		double theta = atan2(target->getLocation().y - getLocation().y, target->getLocation().x - getLocation().x);
		double distance = pythag2(target->getLocation().y - getLocation().y, target->getLocation().x - getLocation().x);
		if (distance < towerRange)
		{
			gunSpr.setRotation(theta * 180 / M_PI);
			fireTimer -= dtAsSeconds;
			if (fireTimer <= 0)
			{
				fireTimer = 1.f / fireRate;
				fire();
				if (target->isActive() == false) 
				{
					validTarget = false;
					gunSpr.setColor(sf::Color::White);
				}
			}
			else 
			{
				if(flashTimeCtr > 0)
				{
					flashTimeCtr -= dtAsSeconds;
					if (flashTimeCtr <= 0)
					{
						gunSpr.setColor(sf::Color::White);
					}
				}
			}
		}
		else
		{
			validTarget = false;
		}
	}
}

void Tower::fire()
{
	gunSpr.setColor(sf::Color::Yellow);
	target->takeDamage(damage);
	flashTimeCtr = flashTime;
}

void Tower::findTarget()
{
	double min_distance = 100000;
	double distance;
	double theta;
	double xd;
	double yd;
	for (auto enemy : getTowerManager()->getGame()->getEnemyManager()->getEnemies())
	{
		if(enemy->isActive())
		{
			xd = enemy->getLocation().x - getLocation().x;
			yd = enemy->getLocation().y - getLocation().y;
			theta = atan2(yd, xd);

			distance = pythag2(xd, yd);
			if (distance < towerRange && distance < min_distance)
			{
				min_distance = distance;
				target = enemy;
				validTarget = true;
			}
		}
	}
}

void Tower::Draw(sf::RenderWindow* context)
{
	if (active)
	{
		context->draw(healthRed);
		context->draw(healthGreen);
		context->draw(spr);
		context->draw(gunSpr);
	}
}

void Tower::setTexture(sf::Texture* texture)
{
	text = texture;
	spr.setTexture(*text);
	spr.setScale(0.25, 0.25);
	
}

void Tower::setGunTexture(sf::Texture* texture)
{
	gunText = texture;
	gunSpr.setTexture(*gunText);
	gunSpr.setScale(0.25, 0.25);
	sf::FloatRect bds = gunSpr.getLocalBounds();
	gunSpr.setOrigin(bds.left + (bds.width / 2.f) - 150, bds.top + (bds.height / 2.f));
}

void Tower::setLocation(sf::Vector2f loc)
{
	location = loc; 
	spr.setPosition(loc); 
	sf::FloatRect bds = spr.getLocalBounds();
	spr.setOrigin(bds.left + (bds.width / 2.f), bds.top + (bds.height / 2.f));

	gunSpr.setPosition(loc);
}
