#pragma once
#include <SFML/Graphics.hpp>

class Tower {
private:
	sf::Vector2f position;
	sf::Vector2f speed;
	double rotation;
	//image file
	//bitmap file
public:
	Tower(const Tower&) = delete;
	void operator=(const Tower&) = delete;
	double GetX() { return position.x; }
	double GetY() { return position.y; }
	sf::Vector2f GetPosition() { return position; }
	double GetXv() { return speed.x; }
	double GetYv() { return speed.y; }
	sf::Vector2f GetSpeed() { return speed; }
	void SetLocation(double x, double y);
	void SetLocation(sf::Vector2f loc);
	void SetSpeed(double x, double y);
	void SetSpeed(sf::Vector2f vel);
	void SetRotation(double rot);
	void Update(double elapsed);
	void Draw();
};