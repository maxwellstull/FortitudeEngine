#define _USE_MATH_DEFINES
#include "include/Enemy.h"
#include "include/EnemyManager.h"
#include "include/Path.h"
#include "include/Game.h"
#include "include/Tower.h"
#include <cmath>
#include <iostream>

double pythag(double x, double y)
{
	return sqrt(pow(x, 2) + pow(y, 2));
}


void Enemy::update(float dtAsSeconds)
{
	if (active)
	{
		location = location + dtAsSeconds * deltaPerSec;
		spr.setPosition(location);
		gunSpr.setPosition(location);
		std::cout << "Location: " << spr.getPosition().x << ", " << spr.getPosition().y << std::endl;
		if (!pathingBounds.contains(location)) //no longer in rectangle - meaning it met the waypoint
		{
			newDestination(enm->getGame()->getMap()->getPath()->getNextDestination(++destinationIdx));
		}

		if (validTarget == false)
		{
			findTarget();
		}
		else
		{
			double theta = atan2(target->getLocation().y - getLocation().y, target->getLocation().x - getLocation().x);
			double distance = pythag(target->getLocation().y - getLocation().y, target->getLocation().x - getLocation().x);
			if (distance < range)
			{
				gunSpr.setRotation(theta * 180 / M_PI);
			}
			else
			{
				gunSpr.setRotation(0);
				validTarget = false;
			}
		}

		if (health <= 0)
		{
			deactivate();
		}
		std::cout << "Health: " << health << std::endl;
	}
}


void Enemy::findTarget()
{
	double min_distance = 100000;
	double distance;
	double theta;
	double xd;
	double yd;
	for (auto tower : getEnemyManager()->getGame()->getTowerManager()->getTowers())
	{
		xd = tower->getLocation().x - getLocation().x;
		yd = tower->getLocation().y - getLocation().y;
		theta = atan2(yd, xd);
		if ((theta < (heading + M_PI_2)) && (theta > (heading - M_PI_2)))
		{
			distance = pythag(xd, yd);
			if (distance < range && distance < min_distance)
			{
				min_distance = distance;
				target = tower;
				validTarget = true;
			}
		}
	}
}



void Enemy::Draw(sf::RenderWindow* context)
{
	if(active)
	{
		context->draw(spr);
		context->draw(gunSpr);
	}
}

void Enemy::setTexture(sf::Texture* texture)
{
	text = texture;
	spr.setTexture(*text);
	spr.setScale(0.25, 0.25);
}

void Enemy::initialize(std::shared_ptr<PathNode> start_node)
{
	location = start_node->location;
	destination = start_node;
	spr.setPosition(location);
	sf::FloatRect bds = spr.getLocalBounds();
	spr.setOrigin(bds.left + (bds.width / 2.f), bds.top + (bds.height / 2.f));
	destinationIdx = 0;
	newDestination(getEnemyManager()->getGame()->getMap()->getPath()->getNextDestination(++destinationIdx));


	maxHealth = 100;
	health = 100;
	damage = 10;
	fireRate = 0.5;
	validTarget = false;
	range = 300;

	activate();

//		sf::FloatRect textRect = viewedText.getLocalBounds();
//	viewedText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

}

void Enemy::newDestination(std::shared_ptr<PathNode> newD)
{
	if (newD->nodeType == PathNodeType::END)
	{
		deactivate();
		getEnemyManager()->getGame()->decrementCurrentHealth();
	}

	float theta = atan2((newD->location.y - location.y), (newD->location.x - location.x));
	heading = theta;
	deltaPerSec.x = speed * cos(theta);
	deltaPerSec.y = speed * sin(theta);

	std::cout <<theta<<" " << deltaPerSec.x << " " << deltaPerSec.y << std::endl;

	lastDestination = destination;
	destination = newD;

	pathingBounds = sf::FloatRect(sf::Vector2f
		(destination->location.x < location.x ? destination->location.x - 1: location.x - 1, 
		 destination->location.y < location.y ? destination->location.y - 1: location.y - 1), 
		sf::Vector2f(
			abs(location.x - destination->location.x) + 1, 
			abs(location.y - destination->location.y) + 2));
}

void Enemy::setGunTexture(sf::Texture* texture)
{
	gunText = texture;
	gunSpr.setTexture(*gunText);
	gunSpr.setScale(0.25, 0.25);
	sf::FloatRect bds = gunSpr.getLocalBounds();
	gunSpr.setOrigin(bds.left + (bds.width / 2.f) - 150, bds.top + (bds.height / 2.f));
	
}





