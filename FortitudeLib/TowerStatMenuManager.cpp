#include "include/TowerStatMenuManager.h"
#include "include/Tower.h"
#include "include/Engine.h"

void TowerStatMenuManager::TowerSplash(std::shared_ptr<Tower> theGuy)
{
	getShapes()->clear();
	getComponents()->clear();

	//location math
	sf::Vector2f guyLoc = theGuy->getLocation();
	int boardOffset = 50;
	sf::Vector2f boardSize = sf::Vector2f(200, 250);
	sf::Vector2f paperSize = sf::Vector2f(180, 230);
	sf::Vector2f windowBounds = GetEngine()->GetWindowManager()->getWindowSize();
	sf::Vector2f boardLocation;

	int splashDirection = 1; //1=above, 2=right, 3=below, 4=left
	if ((guyLoc.y - boardOffset - boardSize.y) < 0) //can't go above
	{
		if ((guyLoc.y + boardOffset + boardSize.y) > windowBounds.y) //cant go below
		{
			if ((guyLoc.x - boardOffset - boardSize.x) < 0) //cant go left
			{
				if ((guyLoc.x + boardOffset + boardSize.x) > windowBounds.x) //cant fit right
				{

				}
				else //can fit right
				{
					boardLocation.x = guyLoc.x + boardOffset + (boardSize.y / 2);
					boardLocation.y = guyLoc.y;
				}
			}
			else //can fit left
			{
				boardLocation.x = guyLoc.x - boardOffset - (boardSize.y / 2);
				boardLocation.y = guyLoc.y;
			}
		}
		else //can fit below
		{
			boardLocation.x = guyLoc.x;
			boardLocation.y = guyLoc.y + boardOffset + (boardSize.x / 2);
		}
	}
	else //can fit above
	{
		boardLocation.x = guyLoc.x;
		boardLocation.y = guyLoc.y - boardOffset - (boardSize.x / 2);
	}

	//background
	std::shared_ptr<sf::RectangleShape> woodenBoard =
		std::make_shared<sf::RectangleShape>(sf::Vector2f(200, 250));
	woodenBoard->setTexture(getTexture(0));
	sf::FloatRect bds = woodenBoard->getLocalBounds();
	woodenBoard->setOrigin(bds.left + (bds.width / 2.f), bds.top + (bds.height / 2.f));
	woodenBoard->setPosition(boardLocation.x, boardLocation.y);
	woodenBoard->setFillColor(sf::Color(255, 255, 255, 150));

	std::shared_ptr<sf::RectangleShape> paper =
		std::make_shared<sf::RectangleShape>(sf::Vector2f(180, 230));
	paper->setTexture(getTexture(1));
	bds = paper->getLocalBounds();
	paper->setOrigin(bds.left + (bds.width / 2.f), bds.top + (bds.height / 2.f));
	paper->setPosition(boardLocation.x, boardLocation.y);
	paper->setFillColor(sf::Color(255, 255, 255, 150));

	//health
	std::shared_ptr<sf::Text> health = std::make_shared<sf::Text>();
	health->setString(theGuy->getHealthString());
	fonty = sf::Font();
	fonty.loadFromFile(getFont(0));
	health->setFont(fonty);
	health->setCharacterSize(20);
	health->setPosition(boardLocation.x - (paperSize.x / 2) + 5, boardLocation.y - (paperSize.y/2) + 30);
	_health = health;
	//damage
	std::shared_ptr<sf::Text> dmg = std::make_shared<sf::Text>();
	dmg->setString(theGuy->getDamageString());
	dmg->setFont(fonty);
	dmg->setCharacterSize(20);
	dmg->setPosition(boardLocation.x - (paperSize.x / 2) + 5, boardLocation.y - (paperSize.y / 2) + 60);
	_damage = dmg;
	//range
	std::shared_ptr<sf::Text> rng = std::make_shared<sf::Text>();
	rng->setString(theGuy->getRangeString());
	rng->setFont(fonty);
	rng->setCharacterSize(20);
	rng->setPosition(boardLocation.x - (paperSize.x / 2) + 5, boardLocation.y - (paperSize.y / 2) + 90);
	_range = rng;
	//accuracy 
	std::shared_ptr<sf::Text> acc = std::make_shared<sf::Text>();
	acc->setString(theGuy->getAccuracyString());
	acc->setFont(fonty);
	acc->setCharacterSize(20);
	acc->setPosition(boardLocation.x - (paperSize.x / 2) + 5, boardLocation.y - (paperSize.y / 2) + 120);
	_accuracy = acc;
	//boolet 
	std::shared_ptr<sf::Text> bullet = std::make_shared<sf::Text>();
	bullet->setString(theGuy->getAmmoString());
	bullet->setFont(fonty);
	bullet->setCharacterSize(20);
	bullet->setPosition(boardLocation.x - (paperSize.x / 2) + 5, boardLocation.y - (paperSize.y / 2) + 150);
	_ammo = bullet;

	getShapes()->push_back(woodenBoard);
	getShapes()->push_back(paper);
	getShapes()->push_back(health);
	getShapes()->push_back(dmg);
	getShapes()->push_back(rng);
	getShapes()->push_back(acc);
	getShapes()->push_back(bullet);
	_splashed = theGuy;
	activate();
}

void TowerStatMenuManager::refresh()
{
	if(isActive())
	{
		_health->setString(_splashed->getHealthString());
		_damage->setString(_splashed->getDamageString());
		_range->setString(_splashed->getRangeString());
		_accuracy->setString(_splashed->getAccuracyString());
		_ammo->setString(_splashed->getAmmoString());
	}
}