#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Path.h"

class Engine;

class Map
{
private:
	sf::Texture tex;
	sf::Sprite spr;
	std::string name;
	Path path;
	bool _initialized;
public:
	Map(const char* mapname, const char* title);
	Map(const char* mapname, const char* title, sf::IntRect rec);
	void Draw(sf::RenderWindow* context);
	sf::Texture* getTexture() { return &tex; }
	std::string getName() { return name; }
	void setSpriteScale(sf::Vector2f scale) { spr.setScale(scale); }
	Path* getPath() { return &path; }
	void initialize();
};