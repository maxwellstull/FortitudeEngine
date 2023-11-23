#pragma once
#include <SFML/Graphics.hpp>
#include "GameStructures.h"
#include "Tower.h"


class Lawman : public Tower
{
private:
	//Special upgrade
	int _rouletteDamageIncrease;
	double _rouletteBulletsPerClip;
	int _rouletteBulletIdx;

public:
	Lawman(Attributes attr);
	void fire();
	//void update(double dt);
	//void draw(sf::RenderWindow* context);

};