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
		std::cout << "Location: " << spr.getPosition().x << ", " << spr.getPosition().y << std::endl;
		if (!pathingBounds.contains(location)) //no longer in rectangle - meaning it met the waypoint
		{
			newDestination(enm->getGame()->getMap()->getPath()->getNextDestination(++destinationIdx));
		}
	}
}

void Enemy::Draw(sf::RenderWindow* context)
{

	sf::RectangleShape r;
	r.setPosition(pathingBounds.getPosition());
	r.setSize(pathingBounds.getSize());
	r.setFillColor(sf::Color::Black);
	context->draw(r);
	context->draw(spr);
}

void Enemy::setTexture(sf::Texture* texture)
{
	text = texture;
	spr.setTexture(*text);
	spr.setScale(0.25, 0.25);
}

void Enemy::initialize(sf::Vector2f loc)
{
	location = loc;
	spr.setPosition(location);
	sf::FloatRect bds = spr.getLocalBounds();
	spr.setOrigin(bds.left + (bds.width / 2.f), bds.top + (bds.height / 2.f));
	destinationIdx = 0;
	newDestination(getEnemyManager()->getGame()->getMap()->getPath()->getNextDestination(++destinationIdx));
	activate();

//		sf::FloatRect textRect = viewedText.getLocalBounds();
//	viewedText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

}

void Enemy::newDestination(PathNode newD)
{
	float theta = atan2((newD.location->y - location.y), (newD.location->x - location.x));
	deltaPerSec.x = speed * cos(theta);
	deltaPerSec.y = speed * sin(theta);

	std::cout <<theta<<" " << deltaPerSec.x << " " << deltaPerSec.y << std::endl;

	lastDestination = std::make_shared<sf::Vector2f>(location);
	destination = newD.location;

	pathingBounds = sf::FloatRect(sf::Vector2f(destination->x < lastDestination->x ? destination->x - 1: lastDestination->x - 1, destination->y < lastDestination->y ? destination->y - 1: lastDestination->y - 1), sf::Vector2f(abs(lastDestination->x - destination->x) + 1, abs(lastDestination->y - destination->y) + 2));	
}