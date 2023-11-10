#include "include/MenuMap.h"
#include <iostream>
MenuMap::MenuMap(const char* label, sf::Font* font, sf::Vector2f position, int size, sf::IntRect rect, sf::Texture * texture)
	: MenuComponent(label, font, sf::Vector2f(position.x+510/2,position.y+370), size)
{
	text = texture;
	outline = sf::RectangleShape(sf::Vector2f(rect.width, rect.height));
	outline.setOrigin((outline.getPosition().x / 2.0f) /* + outline.getSize().x*/, (outline.getPosition().x / 2.0f)/* + outline.getSize().x */ );
	
	outline.setTexture(texture);
	outline.setOutlineColor(sf::Color::Black);
	outline.setOutlineThickness(10);
	outline.setPosition(rect.left, rect.top);
	std::cout << "origin: " << outline.getOrigin().x << " " << outline.getOrigin().y << std::endl;
}
/*MenuMap::MenuMap(const char* label, sf::Font* font, sf::Vector2f position, int size, sf::IntRect rect)
	: MenuComponent(label, font, position, size)
{

}*/
void MenuMap::Draw(sf::RenderWindow* context)
{
	context->draw(outline);
	MenuComponent::Draw(context);
}

void MenuMap::Update(float dtAsSeconds)
{
	MenuComponent::Update(dtAsSeconds);
}

bool MenuMap::hittest(sf::Vector2f cursorPos)
{
	sf::FloatRect bounds = outline.getGlobalBounds();
	return bounds.contains(cursorPos) || MenuComponent::hittest(cursorPos);
}
