#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "GameStructures.h"

class EnemyManager;

class Enemy {
private:
	bool active;
	EnemyManager* enm;
	sf::Vector2f location;
	sf::Vector2f deltaPerSec;
	std::shared_ptr<sf::Vector2f> lastDestination;
	std::shared_ptr<sf::Vector2f> destination;
	std::shared_ptr<sf::FloatRect> endBounds;
	sf::FloatRect pathingBounds;
	int destinationIdx = 0;
	float speed;

	sf::Texture* text;
	sf::Sprite spr;
public:
	void setTexture(sf::Texture* texture);
	void setLocation(sf::Vector2f loc) { location = loc; }
	void setSpeed(int sp) { speed = sp; }
	void setEnemyManager(EnemyManager* e) { enm = e; }
	EnemyManager* getEnemyManager() { return enm; }
	void newDestination(PathNode newD);
	void update(float dtAsSeconds);
	int getDestinationIdx() { return destinationIdx; }
	void Draw(sf::RenderWindow* context);
	void initialize(sf::Vector2f loc);
	void activate() { active = true; }
	void deactivate() { active = false; }
};