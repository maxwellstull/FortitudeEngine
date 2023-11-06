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
	//text.setPosition(sf::Vector2f(context->getView().getSize().x / 2, context->getView().getSize().y / 4));
//	texty.setFont(fonty);
	context->draw(texty);
}