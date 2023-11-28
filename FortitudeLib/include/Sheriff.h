#pragma once
#include <SFML/Graphics.hpp>
#include "GameStructures.h"
#include "Tower.h"

class Sheriff : public Tower
{
private:
	int _ammoCap;
	bool _2ndGunLeft;

	sf::Texture* _2ndGunTex;
	sf::Sprite _2ndGunSpr;

	Animation _2ndGunRecoilAnimation;
	Animation _2ndGunResetAnimation;
	Timer _2ndGunFireTimer;

public:
	Sheriff(Attributes attr);
	void initialize();
	void update(double dtAsSeconds);
	void fire();
	void otherFire();
	void draw(sf::RenderWindow * context);
	void setLocation(sf::Vector2f loc);


	Animation* get2ndResetAnimation() { return &_2ndGunResetAnimation; }

	void setGunTexture(sf::Texture* texture, double scale, sf::Vector2f offset);
	double get2ndAnimationValue();
	void set2ndGunRotation(double rot, double rotmod);
	void Offset2ndGunTimer();
};