#include "include/MenuMap.h"
#include <iostream>
MenuMap::MenuMap(const char* label, sf::Font* font, sf::Vector2f position, int size, sf::IntRect rect, sf::Texture * texture)
	: MenuComponent(label, font, sf::Vector2f(position.x+380,position.y+370), size)
{
	text = texture;
	outline = sf::RectangleShape(sf::Vector2f(rect.width, rect.height));
	outline.setOrigin((outline.getPosition().x / 2.0f) /* + outline.getSize().x*/, (outline.getPosition().x / 2.0f)/* + outline.getSize().x */ );
	
	outline.setTexture(texture);
	outline.setOutlineColor(sf::Color::Black);
	outline.setOutlineThickness(10);
//	outline.setOrigin(rect.width / 2 + rect.left, rect.height / 2 + rect.top);
//	std::cout << rect.width / 2 + rect.left << " " << rect.height / 2 + rect.top << std::endl;
//	outline.setOrigin((outline.getSize().x / 2) + outline.getPosition().x, (outline.getSize().y / 2) + outline.getPosition().y);
	outline.setPosition(rect.left, rect.top);
	std::cout << "origin: " << outline.getOrigin().x << " " << outline.getOrigin().y << std::endl;
}

void MenuMap::Draw(sf::RenderWindow* context)
{
	context->draw(outline);
	MenuComponent::Draw(context);
}

void MenuMap::Update(float dtAsSeconds)
{
	MenuComponent::Update(dtAsSeconds);
}
