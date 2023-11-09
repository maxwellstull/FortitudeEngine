#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Engine;

class Map
{
private:
	sf::Texture tex;
	sf::Sprite spr;
	std::string name;
public:
	void init(const char* mapname, const char* title);
	void Draw(sf::RenderWindow* context);
	sf::Texture* getTexture() { return &tex; }
	std::string getName() { return name; }
};