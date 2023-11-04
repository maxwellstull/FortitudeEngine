#include "include/MenuManager.h"

void MenuManager::Draw(sf::RenderWindow *context)
{
	for (MenuComponent comp : components)
	{
		comp.Draw(context);
	}
}

void MenuManager::init()
{
	sf::Font font;
	font.loadFromFile("img/cowboy.ttf");
	fonts.push_back(font);

	MainMenu();
}

void MenuManager::MainMenu() 
{
	components.clear();



	MenuComponent title;
	sf::Text txt;
	txt.setString("It's High Noon");
	txt.setFillColor(sf::Color::Blue);
	txt.setFont(fonts[0]);
//	txt.setStyle(sf::Text::Bold);
	txt.setCharacterSize(64);
	sf::FloatRect textRect = txt.getLocalBounds();
	txt.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	
	title.text = txt;
	components.push_back(title);


}