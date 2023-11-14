#pragma once
#include <SFML/Graphics.hpp>
#include <vector>



class Path {
private:
	std::vector<std::shared_ptr<sf::Vector2f>> points;
public:
	std::shared_ptr<sf::Vector2f> getNextDestination(int idx) { return points[idx]; }
	void generatePath();
};