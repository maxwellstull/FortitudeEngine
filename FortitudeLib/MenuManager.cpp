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

	MenuComponent title = MenuComponent("It's High Noon", &fonts[0], sf::Vector2f(960, 200), 100);
	MenuComponent achievements = MenuComponent("Achievements", &fonts[0], sf::Vector2f(960, 370), 64);
	MenuComponent options = MenuComponent("Options", &fonts[0], sf::Vector2f(960, 440), 64);
	MenuComponent quit = MenuComponent("Quit", &fonts[0], sf::Vector2f(960, 510), 64);

	components.push_back(title);
	components.push_back(achievements);
	components.push_back(options);
	components.push_back(quit);

}