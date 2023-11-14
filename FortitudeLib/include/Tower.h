#pragma once
#include <SFML/Graphics.hpp>
#include "GameStructures.h"

class TowerManager;
class Enemy;


class Tower {
private:
	TowerManager* twm;

	sf::Vector2f location;
	double rotation;
	
	double maxHealth;
	double health;
	double damage;
	double fireRate;
	double fireTimer;
	double flashTime;
	double flashTimeCtr;
	
	double towerRange;
	bool active;

	sf::Texture* text;
	sf::Sprite spr;

	sf::Texture* gunText;
	sf::Sprite gunSpr;

	sf::RectangleShape healthGreen;
	sf::RectangleShape healthRed;

	std::shared_ptr<Enemy> target;
	bool validTarget;

public:
	void update(double dtAsSeconds);
	void Draw(sf::RenderWindow * context);

	void setTowerManager(TowerManager* t) { twm = t; }
	TowerManager* getTowerManager() { return twm; }
	void activate() { active = true; }
	void deactivate() { active = false; }

	void setTexture(sf::Texture* texture);
	void setGunTexture(sf::Texture* texture);

	void setLocation(sf::Vector2f loc);
	void setHealth(double hp) { health = hp; maxHealth = hp; }
	void setDamage(double dmg) { damage = dmg; }
	void setFireRate(double fr) { fireRate = fr; }

	void initialize();
	void findTarget();
	void fire();

	sf::Vector2f getLocation() { return location; }
};