#define _USE_MATH_DEFINES
#include "include/Politician.h"
#include <cmath>

Politician::Politician(Attributes attr, sf::Texture* tex, double scale) : Enemy(attr)
{
	_bodyTex = tex;
	_bodySpr.setTexture(*_bodyTex);
	_bodySpr.setScale(scale, scale);
	sf::FloatRect bds = _bodySpr.getLocalBounds();
	_bodySpr.setOrigin(bds.left + (bds.width / 2.f), bds.top + (bds.height / 2.f));
}

void Politician::update(float dtAsSeconds)
{
	Enemy::update(dtAsSeconds);
	_bodySpr.setRotation((getHeading() * 180 / M_PI));
}

void Politician::draw(sf::RenderWindow* context)
{
	if (isActive())
	{
		context->draw(_bodySpr);
		drawHealthBar(context);
		drawArmorBar(context);
	}
}

void Politician::setLocation(sf::Vector2f loc)
{
	_bodySpr.setPosition(loc);
	Enemy::setLocation(loc);
}
