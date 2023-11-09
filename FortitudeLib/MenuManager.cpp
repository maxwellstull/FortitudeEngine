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
	title->onEnter([this]() {this->MapSelect(0); });
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
	back->setControlBind(15, 2, 1, 1);
	back->onSelect(sf::Color::Blue, 96, 0.25);
	back->onEnter([this]() {this->MainMenu(); });
	std::shared_ptr<MenuComponent> fullscreen = std::make_shared<MenuComponent>("Fullscreen", &fonts[0], sf::Vector2f(200, 400), 64);
	fullscreen->setControlBind(1, 3, 2, 4);
	fullscreen->onSelect(sf::Color::Blue, 96, 0.25);
	fullscreen->onEnter([this]() {});
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
	vsync->setControlBind(2, 8, 3,6);
	vsync->onSelect(sf::Color::Blue, 96, 0.25);
	vsync->onEnter([this]() {});
	std::shared_ptr<MenuOption> vsOn = std::make_shared<MenuOption>("On", &fonts[0], sf::Vector2f(400, 500), 64, sf::Color::Red);
	vsOn->setControlBind(2, 8, 3, 7);
	vsOn->onSelect(sf::Color::Blue, 96, 0.25);
	vsOn->init(GetEngine()->GetWindowManager()->isVsync());
	std::shared_ptr<MenuOption> vsOff = std::make_shared<MenuOption>("Off", &fonts[0], sf::Vector2f(500, 500), 64, sf::Color::Red);
	vsOff->setControlBind(2, 8, 6, 7);
	vsOff->onSelect(sf::Color::Blue, 96, 0.25);
	vsOff->init(!GetEngine()->GetWindowManager()->isVsync());

	vsOff->onEnter([this, vsOff, vsOn]() {this->GetEngine()->GetWindowManager()->disableVsync(); vsOff->enable(); vsOn->disable(); });
	vsOn->onEnter([this, vsOff, vsOn]() {this->GetEngine()->GetWindowManager()->enableVsync(); vsOff->disable(); vsOn->enable(); });

	std::shared_ptr<MenuComponent> maxFramerate = std::make_shared<MenuComponent>("Max Framerate", &fonts[0], sf::Vector2f(200, 600), 64);
	maxFramerate->setControlBind(3, 15, 8, 9);
	maxFramerate->onSelect(sf::Color::Blue, 96, 0.25);
	maxFramerate->onEnter([this]() {});
	std::shared_ptr<MenuOption> max3 = std::make_shared<MenuOption>("3fps", &fonts[0], sf::Vector2f(500, 600), 64, sf::Color::Red);
	max3->setControlBind(3, 15, 8, 10);
	max3->onSelect(sf::Color::Blue, 96, 0.25);
	max3->init(GetEngine()->GetWindowManager()->getMaxFramerate() == 3);
	std::shared_ptr<MenuOption> max30 = std::make_shared<MenuOption>("30fps", &fonts[0], sf::Vector2f(650, 600), 64, sf::Color::Red);
	max30->setControlBind(3, 15, 9, 11);
	max30->onSelect(sf::Color::Blue, 96, 0.25);
	max30->init(GetEngine()->GetWindowManager()->getMaxFramerate() == 30);
	std::shared_ptr<MenuOption> max60 = std::make_shared<MenuOption>("60fps", &fonts[0], sf::Vector2f(800, 600), 64, sf::Color::Red);
	max60->setControlBind(3, 15, 10,12);
	max60->onSelect(sf::Color::Blue, 96, 0.25);
	max60->init(GetEngine()->GetWindowManager()->getMaxFramerate() == 60);
	std::shared_ptr<MenuOption> max120 = std::make_shared<MenuOption>("120fps", &fonts[0], sf::Vector2f(950, 600), 64, sf::Color::Red);
	max120->setControlBind(3, 15, 11,13);
	max120->onSelect(sf::Color::Blue, 96, 0.25);
	max120->init(GetEngine()->GetWindowManager()->getMaxFramerate() == 120);
	std::shared_ptr<MenuOption> max240 = std::make_shared<MenuOption>("240fps", &fonts[0], sf::Vector2f(1100, 600), 64, sf::Color::Red);
	max240->setControlBind(3, 15, 12,14);
	max240->onSelect(sf::Color::Blue, 96, 0.25);
	max240->init(GetEngine()->GetWindowManager()->getMaxFramerate() ==240);
	std::shared_ptr<MenuOption> uncap = std::make_shared<MenuOption>("UNLIMITED POWER!!1!", &fonts[0], sf::Vector2f(1500, 600), 64, sf::Color::Red);
	uncap->setControlBind(3, 15, 13,14);
	uncap->onSelect(sf::Color::Blue, 96, 0.25);
	uncap->init(GetEngine()->GetWindowManager()->getMaxFramerate() == 0);

	max3->onEnter([this, max3, max30, max60, max120, max240, uncap]() {
		this->GetEngine()->GetWindowManager()->setMaxFramerate(3);
		max3->enable(); max30->disable(); max60->disable(); max120->disable(); max240->disable(); uncap->disable(); });
	max30->onEnter([this, max3, max30, max60, max120, max240, uncap]() {
		this->GetEngine()->GetWindowManager()->setMaxFramerate(30);
		max3->disable(); max30->enable(); max60->disable(); max120->disable(); max240->disable(); uncap->disable(); });
	max60->onEnter([this, max3, max30, max60, max120, max240, uncap]() {
		this->GetEngine()->GetWindowManager()->setMaxFramerate(60);
		max3->disable(); max30->disable(); max60->enable(); max120->disable(); max240->disable(); uncap->disable(); });
	max120->onEnter([this, max3, max30, max60, max120, max240, uncap]() {
		this->GetEngine()->GetWindowManager()->setMaxFramerate(120);
		max3->disable(); max30->disable(); max60->disable(); max120->enable(); max240->disable(); uncap->disable(); });
	max240->onEnter([this, max3, max30, max60, max120, max240, uncap]() {
		this->GetEngine()->GetWindowManager()->setMaxFramerate(240);
		max3->disable(); max30->disable(); max60->disable(); max120->disable(); max240->enable(); uncap->disable(); });
	uncap->onEnter([this, max3, max30, max60, max120, max240, uncap]() {
		this->GetEngine()->GetWindowManager()->setMaxFramerate(0);
		max3->disable(); max30->disable(); max60->disable(); max120->disable(); max240->disable(); uncap->enable(); });

	std::shared_ptr<MenuComponent> showFps = std::make_shared<MenuComponent>("FPS Display", &fonts[0], sf::Vector2f(200, 700), 64);
	showFps->setControlBind(8, 1, 15, 16);
	showFps->onSelect(sf::Color::Blue, 96, 0.25);
	showFps->onEnter([this]() {});
	std::shared_ptr<MenuOption> fpsOn = std::make_shared<MenuOption>("On", &fonts[0], sf::Vector2f(500, 700), 64, sf::Color::Red);
	fpsOn->setControlBind(8, 1, 15, 17);
	fpsOn->onSelect(sf::Color::Blue, 96, 0.25);
	fpsOn->init(GetEngine()->getFps()->isActive());
	std::shared_ptr<MenuOption> fpsOff = std::make_shared<MenuOption>("Off", &fonts[0], sf::Vector2f(700, 700), 64, sf::Color::Red);
	fpsOff->setControlBind(8, 1, 16, 17);
	fpsOff->onSelect(sf::Color::Blue, 96, 0.25);
	fpsOff->init(!GetEngine()->getFps()->isActive());

	fpsOn->onEnter([this, fpsOff, fpsOn]() {this->GetEngine()->getFps()->enable(); fpsOn->enable(); fpsOff->disable(); });
	fpsOff->onEnter([this, fpsOff, fpsOn]() {this->GetEngine()->getFps()->disable(); fpsOn->disable(); fpsOff->enable(); });



	components.push_back(title);		//0
	components.push_back(back);			//1
	components.push_back(fullscreen);	//2
	components.push_back(vsync);		//3
	components.push_back(fsOn);			//4
	components.push_back(fsOff);		//5
	components.push_back(vsOn);			//6
	components.push_back(vsOff);		//7
	components.push_back(maxFramerate);	//8
	components.push_back(max3);			//9
	components.push_back(max30);		//10
	components.push_back(max60);		//11
	components.push_back(max120);		//12
	components.push_back(max240);		//13
	components.push_back(uncap);		//14
	components.push_back(showFps);		//15
	components.push_back(fpsOn);		//16
	components.push_back(fpsOff);		//17

	selected = components[1];
	selected->select();
}

void MenuManager::MapSelect(int page)
{
	components.clear();

	std::vector<sf::IntRect> locations = {
		sf::IntRect(100, 100, 760, 340),
		sf::IntRect(1060, 100, 760, 340),
		sf::IntRect(100, 540, 760, 340),
		sf::IntRect(1060, 540, 760, 340)
	};
	

	int maps_per_page = locations.size();
	int mapsAmnt = GetEngine()->getMaps().size();

	std::vector<int> maps;
	int start = maps_per_page * page;
	int maps_on_page = (start + maps_per_page) < mapsAmnt ? maps_per_page : maps_per_page - (start + maps_per_page - mapsAmnt);

	std::vector<std::vector<int>> binds = {
		{1, maps_on_page >= 3 ? 3 : 1, 1, maps_on_page >= 2 ? 2 : 1},
		{2, maps_on_page >= 4 ? 4 : 2, 1, 2},
		{1, 3, 3, maps_on_page >= 4 ? 4 : 3},
		{2, 4, 3, 4},
	};

	for (int i = start; i < start + maps_per_page; i++)
	{
		if (i < mapsAmnt)
		{
			std::shared_ptr<MenuMap> t1 = std::make_shared<MenuMap>(GetEngine()->getMap(i)->getName().c_str(), &fonts[0], sf::Vector2f(locations[i % 4].left, locations[i % 4].top), 64, locations[i % 4], GetEngine()->getMap(i)->getTexture());
			t1->onSelect(sf::Color::Blue, 96, 0.25);
			t1->setControlBind(binds[i % 4][0]-1, binds[i % 4][1]-1, binds[i % 4][2]-1, binds[i % 4][3]-1);
			components.push_back(t1);
		}
	}
	selected = components[0];
	selected->select();
		
}