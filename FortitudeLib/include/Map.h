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
	Map(const char* mapname, const char* title);
	Map(const char* mapname, const char* title, sf::IntRect rec);
	void Draw(sf::RenderWindow* context);
	sf::Texture* getTexture() { return &tex; }
	std::string getName() { return name; }
	void setSpriteScale(sf::Vector2f scale) { spr.setScale(scale); }
};