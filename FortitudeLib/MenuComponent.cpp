#include "include/MenuComponent.h"

MenuComponent::MenuComponent(const char * label,
	sf::Font *font, sf::Vector2f position, int size)
{
	texty = sf::Text();
	texty.setString(label);
	texty.setFont(*font);
	texty.setPosition(position);
	texty.setCharacterSize(size);

	sf::FloatRect textRect = texty.getLocalBounds();
	texty.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
}

void MenuComponent::Draw(sf::RenderWindow* context)
{
	context->draw(texty);
}