#include "include/MenuManager.h"
#include <iostream>
#include "include/Engine.h"

class Engine;

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
void MenuManager::Enter()
{
	selected->enter();
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
	options->onEnter([this]() {this->Options(); });
	std::shared_ptr<MenuComponent> quit = std::make_shared<MenuComponent>("Quit", &fonts[0], sf::Vector2f(960, 510), 64);
	quit->setControlBind(2, 0, 3, 3);
	quit->onSelect(sf::Color::Blue, 96, 0.25);
	quit->onEnter([this]() {this->GetEngine()->close(); });

	components.push_back(title);
	components.push_back(achievements);
	components.push_back(options);
	components.push_back(quit);

	selected = components[0];
	selected->select();
}

void MenuManager::Options()
{
	components.clear();

	std::shared_ptr<MenuComponent> title = std::make_shared<MenuComponent>("Options", &fonts[0], sf::Vector2f(200, 200), 64);
	title->setControlBind(0, 0, 0, 0);
	title->onSelect(sf::Color::Blue, 96, 0.25);
	std::shared_ptr<MenuComponent> back = std::make_shared<MenuComponent>("Back", &fonts[0], sf::Vector2f(200, 300), 64);
	back->setControlBind(3, 2, 1, 1);
	back->onSelect(sf::Color::Blue, 96, 0.25);
	back->onEnter([this]() {this->MainMenu(); });
	std::shared_ptr<MenuComponent> fullscreen = std::make_shared<MenuComponent>("Fullscreen", &fonts[0], sf::Vector2f(200, 400), 64);
	fullscreen->setControlBind(1, 3, 2, 4);
	fullscreen->onSelect(sf::Color::Blue, 96, 0.25);
	std::shared_ptr<MenuOption> fsOn = std::make_shared<MenuOption>("On", &fonts[0], sf::Vector2f(400, 400), 64, sf::Color::Red);
	fsOn->setControlBind(1, 3, 2, 5);
	fsOn->onSelect(sf::Color::Blue, 96, 0.25);
	fsOn->init(GetEngine()->GetWindowManager()->isFullscreen());
	std::shared_ptr<MenuOption> fsOff = std::make_shared<MenuOption>("Off", &fonts[0], sf::Vector2f(500, 400), 64, sf::Color::Red);
	fsOff->setControlBind(1, 3, 4, 5);
	fsOff->onSelect(sf::Color::Blue, 96, 0.25);
	fsOff->init(!GetEngine()->GetWindowManager()->isFullscreen());

	fsOff->onEnter([this, fsOff, fsOn]() {this->GetEngine()->GetWindowManager()->disableFullscreen(); fsOff->enable(); fsOn->disable(); });
	fsOn->onEnter([this, fsOff, fsOn]() {this->GetEngine()->GetWindowManager()->enableFullscreen(); fsOn->enable(); fsOff->disable(); });
	
	std::shared_ptr<MenuComponent> vsync = std::make_shared<MenuComponent>("Vsync", &fonts[0], sf::Vector2f(200, 500), 64);
	vsync->setControlBind(2, 0, 3, 3);
	vsync->onSelect(sf::Color::Blue, 96, 0.25);


	components.push_back(title);		//0
	components.push_back(back);			//1
	components.push_back(fullscreen);	//2
	components.push_back(vsync);
	components.push_back(fsOn);			//4
	components.push_back(fsOff);		//5


	selected = components[1];
	selected->select();
}

