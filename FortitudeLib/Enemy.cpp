#include "include/Enemy.h"
#include "include/EnemyManager.h"
#include "include/Path.h"
#include "include/Game.h"
#include <cmath>
#include <iostream>

void Enemy::update(float dtAsSeconds)
{
	if(active)
	{
		location = location + dtAsSeconds * deltaPerSec;
		spr.setPosition(location);
		gunSpr.setPosition(location);
		gunSpr.setRotation(gunSpr.getRotation() + 1);
		std::cout << "Location: " << spr.getPosition().x << ", " << spr.getPosition().y << std::endl;
		if (!pathingBounds.contains(location)) //no longer in rectangle - meaning it met the waypoint
		{
			newDestination(enm->getGame()->getMap()->getPath()->getNextDestination(++destinationIdx));
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





