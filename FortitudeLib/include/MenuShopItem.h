#pragma once
#include <SFML/Graphics.hpp>
#include "MenuComponent.h"


class MenuShopItem : public MenuComponent
{
private:
	sf::RectangleShape backdrop;
	sf::Texture* text;
	sf::Sprite spr;
public:
	//	MenuMap(const char* label, sf::Font* font, sf::Vector2f position, int size, sf::IntRect rect);
	//MenuMap(const char* label, sf::Font* font, sf::Vector2f position, int size, sf::IntRect rect, sf::Texture* texture, sf::Vector2f textOffset);
	
	MenuShopItem(const char* label, const char* fontName, sf::IntRect boundaryRect, int textSize, sf::Texture* texture, sf::Vector2f textOffset);
	
	void Draw(sf::RenderWindow* context);
	void Update(float dtAsSeconds);
	bool hittest(sf::Vector2f cursorPos);
	void setFillColor(sf::Color c);
	void setSpriteScale(double x, double y);
	void setSpriteRotation(double rot);
};