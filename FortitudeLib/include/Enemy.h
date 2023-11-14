#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class EnemyManager;

class Enemy {
private:
	EnemyManager* enm;
	sf::Vector2f location;
	sf::Vector2f deltaPerSec;
	std::shared_ptr<sf::Vector2f> lastDestination;
	std::shared_ptr<sf::Vector2f> destination;
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
	void newDestination(std::shared_ptr<sf::Vector2f> newD);
	void update(float dtAsSeconds);
	int getDestinationIdx() { return destinationIdx; }
	void setDestination(std::shared_ptr<sf::Vector2f> dest);
	void Draw(sf::RenderWindow* context);
	void initialize(sf::Vector2f loc);
};