#include "include/Enemy.h"
#include "include/Game.h"
#include "include/Path.h"
#include <cmath>

void Enemy::update(float dtAsSeconds)
{
	location = location + dtAsSeconds * deltaPerSec;

	if (!pathingBounds.contains(location)) //no longer in rectangle - meaning it met the waypoint
	{
		newDestination(game->getMap()->getPath()->getNextDestination(++destinationIdx));
	}
}

void Enemy::newDestination(std::shared_ptr<sf::Vector2f> newD)
{
	float theta = atan2((newD->y - location.y), (newD->x - location.x));
	deltaPerSec.x = speed * cos(theta);
	deltaPerSec.y = speed * sin(theta);

	lastDestination = destination;
	destination = newD;

	pathingBounds = sf::FloatRect(sf::Vector2f(destination->x < lastDestination->x ? destination->x : lastDestination->x, destination->y > lastDestination->y ? destination->y : lastDestination->y), sf::Vector2f(abs(lastDestination->x - destination->x), abs(lastDestination->y - destination->y)));	
}