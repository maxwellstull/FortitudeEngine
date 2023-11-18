#pragma once
#include <SFML/Graphics.hpp>
#include "GameStructures.h"
#include "Unit.h"
#include <string>

class TowerManager;
class Enemy;


class Tower : public Unit {
private:
	TowerManager* twm;
	sf::CircleShape _rangeCircle;
	bool _paused;
	bool _drawRange;
public:
	Tower(Attributes attr);
	void update(double dtAsSeconds);
	void draw(sf::RenderWindow * context) ;
	void drawRangeCircle(sf::RenderWindow* context);
	void setRangeLocation(sf::Vector2f loc) { _rangeCircle.setPosition(loc); }
	void setTowerManager(TowerManager* t) { twm = t; }
	TowerManager* getTowerManager() { return twm; }


	void findTarget();
	bool hittest(sf::Vector2f cursorPos);
	void setDrawRange() 
	{ 
		_drawRange = true;
	}
	void clearDrawRange() { _drawRange = false; }

	void initialize();
	bool isPaused() { return _paused; }
	void pause() { _paused = true; }
	void unpause() { _paused = false; }
	std::string getHealthString();
	std::string getDamageString();
	std::string getRangeString();
	std::string getAccuracyString();
};