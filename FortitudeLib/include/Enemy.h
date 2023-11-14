#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "GameStructures.h"

class Tower;
class EnemyManager;

class Enemy {
private:
	EnemyManager* enm;

	sf::Vector2f location;
	std::shared_ptr<PathNode> lastDestination;
	std::shared_ptr<PathNode> destination;
	std::shared_ptr<sf::FloatRect> endBounds;
	sf::FloatRect pathingBounds;
	int destinationIdx = 0;

	bool active;
	float speed;
	sf::Vector2f deltaPerSec;
	double heading;

	double range;
	double maxHealth;
	double health;
	double damage;
	double fireRate;
	double fireTimer;

	sf::Texture* text;
	sf::Sprite spr;

	sf::Texture* gunText;
	sf::Sprite gunSpr;

	std::shared_ptr<Tower> target;
	bool validTarget;

public:
	void setTexture(sf::Texture* texture);
	void setGunTexture(sf::Texture* texture);
	void setLocation(sf::Vector2f loc) { location = loc; }
	void setSpeed(int sp) { speed = sp; }
	void setEnemyManager(EnemyManager* e) { enm = e; }
	EnemyManager* getEnemyManager() { return enm; }
	void newDestination(std::shared_ptr<PathNode>  newD);
	void update(float dtAsSeconds);
	int getDestinationIdx() { return destinationIdx; }
	void Draw(sf::RenderWindow* context);
	void initialize(std::shared_ptr<PathNode> start_node);
	void activate() { active = true; }
	void deactivate() { active = false; }
	bool isActive() { return active; }
	void findTarget();
	sf::Vector2f getLocation() { return location; }
	void takeDamage(int amnt) { health -= amnt; }
};