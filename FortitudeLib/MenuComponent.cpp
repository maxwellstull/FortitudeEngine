#include "include/MenuComponent.h"

MenuComponent::MenuComponent(const char * label,
	sf::Font *font, sf::Vector2f position, int size)
{
	viewedText = sf::Text();
	viewedText.setString(label);
	viewedText.setFont(*font);
	viewedText.setPosition(position);
	viewedText.setCharacterSize(size);

	sf::FloatRect textRect = viewedText.getLocalBounds();
	viewedText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

}

void MenuComponent::Draw(sf::RenderWindow* context)
{
	context->draw(viewedText);
}

void MenuComponent::onSelect(sf::Color colour, int size)
{
	onDesel.colour = viewedText.getFillColor();
	onDesel.size = viewedText.getCharacterSize();
	onDesel.origin = viewedText.getOrigin();

	onSel.colour = colour;
	onSel.size = size;

	viewedText.setCharacterSize(onSel.size);
	sf::FloatRect textRect = viewedText.getLocalBounds();
	viewedText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	onSel.origin = viewedText.getOrigin();

	viewedText.setOrigin(onDesel.origin);
	viewedText.setCharacterSize(onDesel.size);

}

void MenuComponent::select()
{
	viewedText.setFillColor(onSel.colour);
	viewedText.setCharacterSize(onSel.size);
	viewedText.setOrigin(onSel.origin);
}

void MenuComponent::deselect()
{
	viewedText.setFillColor(onDesel.colour);
	viewedText.setCharacterSize(onDesel.size);
	viewedText.setOrigin(onDesel.origin);
}