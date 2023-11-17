#pragma once
#include <SFML/Graphics.hpp>
#include "GameStructures.h"
#include "Unit.h"

class TowerManager;
class Enemy;


class Tower : public Unit {
private:
	TowerManager* twm;
	sf::CircleShape _rangeCircle;
	bool _paused;
public:
	Tower(Attributes attr);
	void update(double dtAsSeconds);
	void draw(sf::RenderWindow * context);
	void drawRangeCircle(sf::RenderWindow* context);
	void setRangeLocation(sf::Vector2f loc) { _rangeCircle.setPosition(loc); }
	void setTowerManager(TowerManager* t) { twm = t; }
	TowerManager* getTowerManager() { return twm; }


	void findTarget();

	void initialize();
	void pause() { _paused = true; }
	void unpause() { _paused = false; }
};