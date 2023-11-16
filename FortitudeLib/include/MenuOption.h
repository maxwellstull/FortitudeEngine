#pragma once
#include <SFML/Graphics.hpp>
#include "MenuComponent.h"
#include <vector>

class MenuOption : public MenuComponent
{
private:
	sf::Color enableColor;
	sf::Color disableColor;
public:
	MenuOption(const char* label,
		const char* fontName, sf::Vector2f position, int size, sf::Color eC);
	void Draw(sf::RenderWindow* context);
	void Update(float dtAsSeconds);
	void setEnableColor(sf::Color c) { enableColor = c; }
	void init(bool en);
	void disable() { MenuComponent::setColor(disableColor); }
	void enable() { MenuComponent::setColor(enableColor); }
};