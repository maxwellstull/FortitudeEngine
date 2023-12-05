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
	int uniqueID;

	float speed;
	
	double heading;
public:
	Enemy(Attributes attr);
	virtual void update(float dtAsSeconds);
	void draw(sf::RenderWindow* context);
	void findTarget();
	double getHeading() { return heading; }
	void setSpeed(int sp) { speed = sp; }
	void setEnemyManager(EnemyManager* e) { enm = e; }
	EnemyManager* getEnemyManager() { return enm; }
	void nextDestination();
	int getDestinationIdx() { return destinationIdx; }
	void setID(int uid) { uniqueID = uid; }
	int getID() { return uniqueID; }

	void initialize(PathSegment * st);
	void splashDamageAssist(double rng, double dmg, sf::Vector2f origin, double dropoffCoeff);
	void fire();
};