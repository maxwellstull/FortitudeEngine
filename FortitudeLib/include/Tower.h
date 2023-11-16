#pragma once
#include <SFML/Graphics.hpp>
#include "GameStructures.h"
#include "Unit.h"

class TowerManager;
class Enemy;


class Tower : public Unit {
private:
	TowerManager* twm;
	bool _paused;
public:
	Tower(Attributes attr);
	void update(double dtAsSeconds);
	void draw(sf::RenderWindow * context);

	void setTowerManager(TowerManager* t) { twm = t; }
	TowerManager* getTowerManager() { return twm; }

	void findTarget();

	void initialize();
	void pause() { _paused = true; }
	void unpause() { _paused = false; }
};