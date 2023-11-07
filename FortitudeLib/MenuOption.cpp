#include "include/MenuOption.h"
#include <iostream>

MenuOption::MenuOption(const char* label, sf::Font* font, sf::Vector2f position, int size, sf::Color eC) :
	MenuComponent(label, font, position, size)
{
	enableColor = eC;
}

void MenuOption::Draw(sf::RenderWindow* context)
{
	MenuComponent::Draw(context);
}

void MenuOption::Update(float dtAsSeconds)
{
}

void MenuOption::init(bool en)
{
	disableColor = MenuComponent::getColor();
	if (en == true)
	{
		enable();
	}
	else
	{
		disable();
	}
}