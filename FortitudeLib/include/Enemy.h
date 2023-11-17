#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "GameStructures.h"
#include "Unit.h"
#include "PathSegment.h"

class Tower;
class EnemyManager;

class Enemy : public Unit {
private:
	EnemyManager* enm;

//	std::shared_ptr<PathNode> lastDestination;
	PathSegment * destination;
//	std::shared_ptr<sf::FloatRect> endBounds;
//	sf::FloatRect pathingBounds;
	int destinationIdx = 0;

	float speed;
	
	double heading;
public:
	Enemy(Attributes attr);
	void update(float dtAsSeconds);
	void draw(sf::RenderWindow* context);
	void findTarget();

	void setSpeed(int sp) { speed = sp; }
	void setEnemyManager(EnemyManager* e) { enm = e; }
	EnemyManager* getEnemyManager() { return enm; }
	void nextDestination();
	int getDestinationIdx() { return destinationIdx; }
	
	void initialize(PathSegment * st);
};