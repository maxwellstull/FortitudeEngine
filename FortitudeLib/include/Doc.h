#pragma once
#include <SFML/Graphics.hpp>
#include "GameStructures.h"
#include "Tower.h"

class Doc : public Tower
{
private:

public:
	Doc(Attributes attr);
	void initialize();
	void update(double dtAsSeconds);
	void fire();
	void findTarget();
	
};