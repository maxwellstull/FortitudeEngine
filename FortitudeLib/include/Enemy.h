#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "GameStructures.h"
#include "Unit.h"

class Tower;
class EnemyManager;

class Enemy : public Unit {
private:
	EnemyManager* enm;

	std::shared_ptr<PathNode> lastDestination;
	std::shared_ptr<PathNode> destination;
	std::shared_ptr<sf::FloatRect> endBounds;
	sf::FloatRect pathingBounds;
	int destinationIdx = 0;

	float speed;
	sf::Vector2f deltaPerSec;
	double heading;
public:
	Enemy(Attributes attr);
	void update(float dtAsSeconds);
	void draw(sf::RenderWindow* context);
	void findTarget();

	void setSpeed(int sp) { speed = sp; }
	void setEnemyManager(EnemyManager* e) { enm = e; }
	EnemyManager* getEnemyManager() { return enm; }
	void newDestination(std::shared_ptr<PathNode>  newD);
	int getDestinationIdx() { return destinationIdx; }
	
	void initialize(std::shared_ptr<PathNode> start_node);
};