#include "include/MenuComponent.h"

MenuComponent::MenuComponent()
{
	fonty = sf::Font();
	fonty.loadFromFile("img/cowboy.ttf");

	//	MenuComponent title;
	//sf::Text txt;
	//txt.setString("Hello, World!");
	//txt.setFillColor(sf::Color::Blue);
	//txt.setFont(fonty);
	//txt.setStyle(sf::Text::Bold | sf::Text::Underlined);
	//txt.setPosition(100, 100);
	//text = txt;
}

void MenuComponent::Draw(sf::RenderWindow* context)
{
/*	sf::Font font;
	font.loadFromFile("img/cowboy.ttf");
	fonty = font;
	//	MenuComponent title;
	sf::Text txt;
	txt.setString("Hello, World!");
	txt.setFillColor(sf::Color::Blue);
	txt.setFont(fonty);
	txt.setStyle(sf::Text::Bold | sf::Text::Underlined);
	txt.setPosition(100, 100);
	text = txt;
	*/
	text.setPosition(sf::Vector2f(context->getView().getSize().x / 2, context->getView().getSize().y / 4));
	text.setFont(fonty);
	context->draw(text);
}