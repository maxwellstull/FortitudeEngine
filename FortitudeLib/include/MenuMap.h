#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "MenuComponent.h"


class MenuMap : public MenuComponent
{
private:
	sf::RectangleShape outline;
	sf::Texture * text;
public:
//	MenuMap(const char* label, sf::Font* font, sf::Vector2f position, int size, sf::IntRect rect);
	MenuMap(const char* label, sf::Font* font, sf::Vector2f position, int size, sf::IntRect rect, sf::Texture * texture);
	void Draw(sf::RenderWindow* context);
	void Update(float dtAsSeconds);
	bool hittest(sf::Vector2f cursorPos);

};