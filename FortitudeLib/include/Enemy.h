#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class Game;

class Enemy {
private:
	Game* game;
	sf::Vector2f location;
	sf::Vector2f deltaPerSec;
	std::shared_ptr<sf::Vector2f> lastDestination;
	std::shared_ptr<sf::Vector2f> destination;
	sf::FloatRect pathingBounds;
	int destinationIdx;
	float speed;
public:
	void newDestination(std::shared_ptr<sf::Vector2f> newD);
	void update(float dtAsSeconds);
};