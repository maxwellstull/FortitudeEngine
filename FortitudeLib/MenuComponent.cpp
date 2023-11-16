#include "include/MenuComponent.h"
#include <iostream>

MenuComponent::MenuComponent(const char * label,
	const char * fontName, sf::Vector2f position, int size)
{
	font = sf::Font();
	font.loadFromFile(fontName);
	viewedText = sf::Text();
	viewedText.setString(label);
	viewedText.setFont(font);
	viewedText.setCharacterSize(size);
	viewedText.setPosition(position);
	sf::FloatRect textRect = viewedText.getLocalBounds();
	viewedText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	
	funky = []() {};
}

void MenuComponent::Update(float dtAsSeconds)
{
	if (anim.active == true)
	{
		float curSize = viewedText.getCharacterSize() + (((anim.elapsed + dtAsSeconds) / anim.duration) * (anim.end - anim.start));
		if ((anim.increase == true) && (curSize > anim.end))
		{
			curSize = anim.end;
			anim.active = false;
		}
		else if ((anim.increase == false) && (curSize < anim.end))
		{
			curSize = anim.end;
			anim.active = false;
		}
		viewedText.setCharacterSize((int)curSize);
		sf::FloatRect textRect = viewedText.getLocalBounds();
		viewedText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		anim.elapsed = anim.elapsed + dtAsSeconds;
	}
}

void MenuComponent::Draw(sf::RenderWindow* context)
{
	context->draw(viewedText);
}

void MenuComponent::onSelect(sf::Color colour, int size, float duration)
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
void MenuComponent::setColor(sf::Color c)
{
	onDesel.colour = c;
	viewedText.setFillColor(c);
}
bool MenuComponent::hittest(sf::Vector2f cursorPos)
{
	sf::FloatRect bounds = viewedText.getGlobalBounds();
	return bounds.contains(cursorPos);
}
void MenuComponent::select()
{
	viewedText.setFillColor(onSel.colour);
//	viewedText.setCharacterSize(onSel.size);
//	viewedText.setOrigin(onSel.origin);
	anim.start = onDesel.size;
	anim.end = onSel.size;
	anim.duration = 0.25;
	anim.elapsed = 0.;
	anim.active = true;
	anim.increase = true;
}

void MenuComponent::deselect()
{
	viewedText.setFillColor(onDesel.colour);
//	viewedText.setCharacterSize(onDesel.size);
//	viewedText.setOrigin(onDesel.origin);
	anim.start = onSel.size;
	anim.end = onDesel.size;
	anim.duration = 0.25;
	anim.elapsed = 0.;
	anim.active = true;
	anim.increase = false;
}

void MenuComponent::onEnter(std::function<void()> func)
{
	funky = func;
}

void MenuComponent::enter()
{
	funky();
}