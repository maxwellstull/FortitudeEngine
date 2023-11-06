#include "include/MenuManager.h"
#include <iostream>

void MenuManager::Draw(sf::RenderWindow *context)
{
	for (auto comp : components)
	{
		comp->Draw(context);
	}
}
void MenuManager::update(float dtAsSeconds)
{
	for (auto comp : components)
	{
		comp->Update(dtAsSeconds);
	}
}
void MenuManager::SelectUp()
{
	int idx = selected->onUp();
	selected->deselect();
	selected = components[idx];
	selected->select();
}
void MenuManager::SelectDown()
{
	int idx = selected->onDown();
	selected->deselect();
	selected = components[idx];
	selected->select();
}
void MenuManager::SelectLeft()
{
	int idx = selected->onLeft();
	selected->deselect();
	selected = components[idx];
	selected->select();

}
void MenuManager::SelectRight()
{
	int idx = selected->onRight();
	selected->deselect();
	selected = components[idx];
	selected->select();

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

	std::shared_ptr<MenuComponent> title = std::make_shared<MenuComponent>("It's High Noon", &fonts[0], sf::Vector2f(960, 200), 100);
	title->setControlBind(3, 1, 0, 0);
	title->onSelect(sf::Color::Blue, 200, 0.25);
	std::shared_ptr<MenuComponent> achievements = std::make_shared<MenuComponent>("Achievements", &fonts[0], sf::Vector2f(960, 370), 64);
	achievements->setControlBind(0, 2, 1, 1);
	achievements->onSelect(sf::Color::Blue, 96, 0.25);
	std::shared_ptr<MenuComponent> options = std::make_shared<MenuComponent>("Options", &fonts[0], sf::Vector2f(960, 440), 64);
	options->setControlBind(1, 3, 2, 2);
	options->onSelect(sf::Color::Blue, 96, 0.25);
	std::shared_ptr<MenuComponent> quit = std::make_shared<MenuComponent>("Quit", &fonts[0], sf::Vector2f(960, 510), 64);
	quit->setControlBind(2, 0, 3, 3);
	quit->onSelect(sf::Color::Blue, 96, 0.25);

	components.push_back(title);
	components.push_back(achievements);
	components.push_back(options);
	components.push_back(quit);

	selected = components[0];
	selected->select();
}

void MenuManager::Options()
{

}