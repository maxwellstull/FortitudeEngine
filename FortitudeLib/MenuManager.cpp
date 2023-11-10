#include "include/MenuManager.h"
#include <iostream>
#include "include/Engine.h"
#include <string>
class Engine;

void MenuManager::Draw(sf::RenderWindow *context)
{
	if(active)
	{
		for (auto shape : shapes)
		{
			context->draw(*shape);
		}
		for (auto comp : components)
		{
			comp->Draw(context);
		}
	}
}
void MenuManager::update(float dtAsSeconds)
{
	if(active)
	{
		for (auto comp : components)
		{
			comp->Update(dtAsSeconds);
		}
	}
}
void MenuManager::SelectUp()
{
	last_active = inputMethod::KEYBOARD;
	int idx = selected->onUp();
	selected->deselect();
	selected = components[idx];
	selected->select();
}
void MenuManager::SelectDown()
{
	last_active = inputMethod::KEYBOARD;
	int idx = selected->onDown();
	selected->deselect();
	selected = components[idx];
	selected->select();
}
void MenuManager::SelectLeft()
{
	last_active = inputMethod::KEYBOARD;
	int idx = selected->onLeft();
	selected->deselect();
	selected = components[idx];
	selected->select();

}
void MenuManager::SelectRight()
{
	last_active = inputMethod::KEYBOARD;
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

	sf::Texture texture;
	texture.loadFromFile("img/wood.jpg");
	textures.push_back(texture);
	MainMenu();
}


void MenuManager::MainMenu() 
{
	shapes.clear();
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
	shapes.clear();
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
	std::vector<sf::IntRect> locations = {
		sf::IntRect(380, 100, 510, 340),
		sf::IntRect(1030, 100, 510, 340),
		sf::IntRect(380, 640, 510, 340),
		sf::IntRect(1030, 640, 510, 340)
	};


	int maps_per_page = locations.size();
	shapes.clear();
	components.clear();

	std::shared_ptr<MenuComponent> mainMenu = std::make_shared<MenuComponent>("Main\nMenu", &fonts[0], sf::Vector2f(182, 170), 64);
	mainMenu->setControlBind(0, 1, 6, 0);
	mainMenu->onSelect(sf::Color::Blue, 96, 0.25);
	mainMenu->onEnter([this]() { this->MainMenu(); });
	std::shared_ptr<MenuComponent> waves = std::make_shared<MenuComponent>("Waves", &fonts[0], sf::Vector2f(182, 300), 64);
	waves->setControlBind(0, 2, 6, 1);
	waves->onSelect(sf::Color::Blue, 96, 0.25);
	std::shared_ptr<MenuOption> w25 = std::make_shared<MenuOption>("25", &fonts[0], sf::Vector2f(100, 350), 32, sf::Color::Red);
	w25->setControlBind(1, 5, 2, 3);
	w25->onSelect(sf::Color::Blue, 48, 0.25);
	w25->init(GetEngine()->getGame()->getWaveCt() == 25);
	std::shared_ptr<MenuOption> w50 = std::make_shared<MenuOption>("50", &fonts[0], sf::Vector2f(150, 350), 32, sf::Color::Red);
	w50->setControlBind(1, 5, 2, 4);
	w50->onSelect(sf::Color::Blue, 48, 0.25);
	w50->init(GetEngine()->getGame()->getWaveCt() == 50);
	std::shared_ptr<MenuOption> w100 = std::make_shared<MenuOption>("100", &fonts[0], sf::Vector2f(200, 350), 32, sf::Color::Red);
	w100->setControlBind(1, 5, 3, 4);
	w100->onSelect(sf::Color::Blue, 48, 0.25);
	w100->init(GetEngine()->getGame()->getWaveCt() == 100);
	
	waves->onEnter([this, w25, w50, w100]() {
		switch (GetEngine()->getGame()->getWaveCt())
		{
			case 25:
			{
				GetEngine()->getGame()->setWaveCt(50);
				w25->disable(); w50->enable(); w100->disable();
				break;
			}
			case 50:
			{
				GetEngine()->getGame()->setWaveCt(100);
				w25->disable(); w50->disable(); w100->enable();
				break;
			}
			case 100:
			{
				GetEngine()->getGame()->setWaveCt(25);
				w25->enable(); w50->disable(); w100->disable();
				break;
			}
		}
		});
	w25->onEnter([this, w25, w50, w100]() {GetEngine()->getGame()->setWaveCt(25); w25->enable(); w50->disable(); w100->disable(); });
	w50->onEnter([this, w25, w50, w100]() {GetEngine()->getGame()->setWaveCt(50); w25->disable(); w50->enable(); w100->disable(); });
	w100->onEnter([this, w25, w50, w100]() {GetEngine()->getGame()->setWaveCt(100); w25->disable(); w50->disable(); w100->enable(); });

	std::shared_ptr<MenuComponent> leaderboard = std::make_shared<MenuComponent>("Leaderboard", &fonts[0], sf::Vector2f(182, 400), 64);
	leaderboard->setControlBind(1, 6, 5, 5);
	leaderboard->onSelect(sf::Color::Blue, 96, 0.25);
	std::shared_ptr<MenuOption> global = std::make_shared<MenuOption>("Global", &fonts[0], sf::Vector2f(100, 450), 32, sf::Color::Red);
	global->setControlBind(5, 8, 6, 7);
	global->onSelect(sf::Color::Blue, 48, 0.25);
	global->init(GetEngine()->getLeaderboard()->getPeopleFilter() == Leaderboard::Filter::GLOBAL);
	std::shared_ptr<MenuOption> friends = std::make_shared<MenuOption>("Friends", &fonts[0], sf::Vector2f(200, 450), 32, sf::Color::Red);
	friends->setControlBind(5, 9, 6, 7);
	friends->onSelect(sf::Color::Blue, 48, 0.25);
	friends->init(GetEngine()->getLeaderboard()->getPeopleFilter() == Leaderboard::Filter::FRIENDS);
	std::shared_ptr<MenuOption> time = std::make_shared<MenuOption>("Time", &fonts[0], sf::Vector2f(100, 500), 32, sf::Color::Red);
	time->setControlBind(6, 0, 8, 9);
	time->onSelect(sf::Color::Blue, 48, 0.25);
	time->init(GetEngine()->getLeaderboard()->getStatFilter() == Leaderboard::Filter::TIME);
	std::shared_ptr<MenuOption> maxwave = std::make_shared<MenuOption>("Max Wave", &fonts[0], sf::Vector2f(200, 500), 32, sf::Color::Red);
	maxwave->setControlBind(7, 0, 8, 9);
	maxwave->onSelect(sf::Color::Blue, 48, 0.25);
	maxwave->init(GetEngine()->getLeaderboard()->getStatFilter() == Leaderboard::Filter::WAVES);

	leaderboard->onEnter([this, global, friends, time, maxwave]() {
		GetEngine()->getLeaderboard()->setPeopleFilter(Leaderboard::Filter::GLOBAL);
		GetEngine()->getLeaderboard()->setStatFilter(Leaderboard::Filter::TIME);
		global->enable(); friends->disable(); time->enable(); maxwave->disable();});
	global->onEnter([this, global, friends]() {
		GetEngine()->getLeaderboard()->setPeopleFilter(Leaderboard::Filter::GLOBAL);
		global->enable(); friends->disable();});
	friends->onEnter([this, global, friends]() {
		GetEngine()->getLeaderboard()->setPeopleFilter(Leaderboard::Filter::FRIENDS);
		global->disable(); friends->enable();});
	time->onEnter([this, time, maxwave]() {
		GetEngine()->getLeaderboard()->setStatFilter(Leaderboard::Filter::TIME);
		time->enable(); maxwave->disable();});
	maxwave->onEnter([this, time, maxwave]() {
		GetEngine()->getLeaderboard()->setStatFilter(Leaderboard::Filter::WAVES);
		time->disable(); maxwave->enable();});

	//Page navigation
	std::shared_ptr<MenuComponent> lastPage = std::make_shared<MenuComponent>("Last Page", &fonts[0], sf::Vector2f(1722, 170), 64);
	lastPage->onSelect(sf::Color::Blue, 96, 0.25);
	std::shared_ptr<MenuComponent> nextPage = std::make_shared<MenuComponent>("Next Page", &fonts[0], sf::Vector2f(1722, 270), 64);
	nextPage->onSelect(sf::Color::Blue, 96, 0.25);
	std::string pgStr = std::to_string(page + 1) + "/" + std::to_string((int)std::ceil(((float)GetEngine()->getMaps().size() / (float)maps_per_page)));
	std::shared_ptr<MenuComponent> pageCt = std::make_shared<MenuComponent>(pgStr.c_str(), &fonts[0], sf::Vector2f(1722, 370), 64);
	pageCt->onSelect(sf::Color::Blue, 96, 0.25);


	components.push_back(mainMenu);		//0
	components.push_back(waves);		//1
	components.push_back(w25);			//2
	components.push_back(w50);			//3
	components.push_back(w100);			//4
	components.push_back(leaderboard);	//5
	components.push_back(global);		//6
	components.push_back(friends);		//7
	components.push_back(time);			//8
	components.push_back(maxwave);		//9

	components.push_back(lastPage);
	components.push_back(nextPage);
	components.push_back(pageCt);





	
	int mapsAmnt = GetEngine()->getMaps().size();
	int comps = components.size();
	std::vector<int> maps;
	int start = maps_per_page * page;
	int maps_on_page = (start + maps_per_page) < mapsAmnt ? maps_per_page : maps_per_page - (start + maps_per_page - mapsAmnt);

	std::vector<std::vector<int>> binds = {
		{comps + 1, comps + (maps_on_page >= 3 ? 3 : 1), 1, comps + (maps_on_page >= 2 ? 2 : 1)},
		{comps + 2, comps + (maps_on_page >= 4 ? 4 : 2), comps + 1, comps + 2},
		{comps + 1, comps + 3, comps + 3, comps + (maps_on_page >= 4 ? 4 : 3)},
		{comps + 2, comps + 4, comps + 3, comps + 4},
	};

	for (int i = start; i < start + maps_per_page; i++)
	{
		if (i < mapsAmnt)
		{
			std::shared_ptr<MenuMap> t1 = std::make_shared<MenuMap>(GetEngine()->getMap(i)->getName().c_str(), &fonts[0], sf::Vector2f(locations[i % 4].left, locations[i % 4].top), 64, locations[i % 4], GetEngine()->getMap(i)->getTexture());
			t1->onSelect(sf::Color::Blue, 96, 0.25);
			t1->setControlBind(binds[i % 4][0]-1, binds[i % 4][1]-1, binds[i % 4][2]-1, binds[i % 4][3]-1);
			t1->onEnter([this, i]() {GetEngine()->setMap(i); components.clear(); this->deactivate(); });
			components.push_back(t1);
		}
	}
	selected = components[comps];
	selected->select();
	

	

	std::shared_ptr<sf::RectangleShape> boardLeft = 
		std::make_shared<sf::RectangleShape>(sf::Vector2f(275, 880));
	boardLeft->setTexture(&textures[0]);
	boardLeft->setPosition(45, 100);

	std::shared_ptr<sf::RectangleShape> boardRight =
		std::make_shared<sf::RectangleShape>(sf::Vector2f(275, 880));
	boardRight->setTexture(&textures[0]);
	boardRight->setPosition(1585, 100);


	shapes.push_back(boardLeft);
	shapes.push_back(boardRight);
}

void MenuManager::hitvisit(sf::Vector2f cursorPos)
{
	if(active)
	{
		for (std::shared_ptr<MenuComponent> component : components)
		{
			if (component->hittest(cursorPos))
			{
				last_active = inputMethod::MOUSE;
				selected->deselect();
				selected = component;
				selected->select();
			}
		}
		if (selected->hittest(cursorPos) == false && last_active==inputMethod::MOUSE)
		{
			selected->deselect();
		}
	}
}