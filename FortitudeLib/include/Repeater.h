#pragma once
#include <SFML/Graphics.hpp>
#include "GameStructures.h"
#include "Tower.h"
#include "Timer.h"

class Repeater : public Tower
{
private:
	double _pocketSandBlindDuration;
	sf::Texture* _pocketSandTexture;
	double _pocketSandScale;

public:
	Repeater(Attributes attr, sf::Texture* tex, double scale);
	void fire();
	void queueReload();
	void setPocketSandTexture(sf::Texture* tex, double scale);
	double getPocketSandDuration() { return _pocketSandBlindDuration; }
};