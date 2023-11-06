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
	std::vector<const char*> labels = { "It's High Noon" };// , "Achievements", "Options", "Quit"};

	MenuComponent title = MenuComponent("It's High Noon", &fonts[0], sf::Vector2f(10, 10), 64);

	components.push_back(title);
/*	MenuComponent title;
	sf::Text txt;
	txt.setString("It's High Noon");

	txt.setFillColor(sf::Color::Blue);
	txt.setFont(fonts[0]);
	txt.setCharacterSize(64);
	sf::FloatRect textRect = txt.getLocalBounds();
	txt.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	title.text = txt;
	components.push_back(title);
	*/
}