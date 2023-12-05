#define _USE_MATH_DEFINES
#include "include/TrainRobber.h"
#include <cmath>

TrainRobber::TrainRobber(Attributes attr, sf::Texture * tex, double scale) : Enemy(attr)
{
	setHorseTexture(tex, scale);
}

void TrainRobber::update(float dtAsSeconds)
{
	Enemy::update(dtAsSeconds);
//	std::cout << "hu" << std::endl;
	
	_horseSprite.setRotation((getHeading() * 180 / M_PI) + 90);
}

void TrainRobber::draw(sf::RenderWindow* context)
{
	if (isActive())
	{
		context->draw(_horseSprite);
	}
	Enemy::draw(context);
}

void TrainRobber::setHorseTexture(sf::Texture* tex, double scale)
{
	_horseTexture = tex;
	_horseSprite.setTexture(*_horseTexture);
	_horseSprite.setScale(scale, scale);
	sf::FloatRect bds = _horseSprite.getLocalBounds();
	_horseSprite.setOrigin(bds.left + (bds.width / 2.f), bds.top + (bds.height / 2.f));
}

void TrainRobber::setLocation(sf::Vector2f loc)
{
	_horseSprite.setPosition(loc);
	Enemy::setLocation(loc);
}
