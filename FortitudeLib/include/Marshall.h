#pragma once
#include <SFML/Graphics.hpp>
#include "GameStructures.h"
#include "Tower.h"

class Marshall : public Tower
{
private:
	double _armorPiercing;
public:
	Marshall(Attributes attr);
	void fire();
};