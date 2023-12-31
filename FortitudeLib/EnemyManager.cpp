#include "include/EnemyManager.h"
#include "include/Game.h"
#include "include/TrainRobber.h"
#include "include/Politician.h"
#include "include/GoldRusher.h"

void EnemyManager::update(float dtAsSeconds)
{
	for (std::shared_ptr<Enemy> en : enemies)
	{
		//Update location
		en->update(dtAsSeconds);
	}
}

void EnemyManager::initialize(GameInfo info)
{
	//load textures
	sf::Texture texture;
	texture.loadFromFile("img/hat.png");
	textures.push_back(texture);
	texture.loadFromFile("img/gun.png");
	textures.push_back(texture);
	texture.loadFromFile("img/bullet.png");
	textures.push_back(texture);
	texture.loadFromFile("img/badhorse.png");
	textures.push_back(texture);
	texture.loadFromFile("img/politician.png");
	textures.push_back(texture);
	texture.loadFromFile("img/mininghelmet.png");
	textures.push_back(texture);
	texture.loadFromFile("img/pickaxe.png");
	textures.push_back(texture);
	enemyIDCtr = 0;

	//spawnBadGuy();
}

void EnemyManager::Draw(sf::RenderWindow* context)
{
	for (std::shared_ptr<Enemy> en : enemies)
	{
		en->draw(context);
	}
}

void EnemyManager::spawnBadGuy() 
{
	Unit::Attributes attr = { 
    100,  //current health
    2,   //damage
    1,  // fire rate
    300,  // range (in pixels)
    80,   //accuracy (0 to 100)
    500,   //projectile speed
		50,		//armor
  };
	Unit::AmmoInfo ami = { 6, 6 };
	std::shared_ptr<Enemy> en = std::make_shared<Enemy>(attr);
	en->setBodyTexture(&textures[0], 0.25);
	en->setGunTexture(&textures[1], 0.25, sf::Vector2f(-150, 0));
	en->setEnemyManager(this);
	en->setAmmoInfo(ami);
	en->setProjTexture(&textures[2], 0.25);
	en->setSpeed(50);
	en->enableArmor();
	en->initialize(getGame()->getMap()->getPath()->getStartSegment());
	en->setID(enemyIDCtr++);
	enemies.push_back(en);
}

void EnemyManager::spawnTrainRobber()
{
	Unit::Attributes attr = {
	200,  //current health
	4,   //damage
	0.5,  // fire rate
	400,  // range (in pixels)
	50,   //accuracy (0 to 100)
	500,   //projectile speed
		100,		//armor
	};
	Unit::AmmoInfo ami = { 6, 6 };
	std::shared_ptr<TrainRobber> en = std::make_shared<TrainRobber>(attr, &textures[3], 0.15);
	en->setBodyTexture(&textures[0], 0.25);
	en->setGunTexture(&textures[1], 0.25, sf::Vector2f(-150, 0));
	en->setEnemyManager(this);
	en->setAmmoInfo(ami);
	en->setProjTexture(&textures[2], 0.25);
	en->setSpeed(100);
	en->enableArmor();
	en->initialize(getGame()->getMap()->getPath()->getStartSegment());
	en->setID(enemyIDCtr++);
	enemies.push_back(en);
}

void EnemyManager::spawnPolitician()
{
	Unit::Attributes attr = {
	500,  //current health
	0,   //damage
	0,  // fire rate
	0,  // range (in pixels)
	0,   //accuracy (0 to 100)
	0,   //projectile speed
	500,		//armor
	};
	Unit::AmmoInfo ami = { 0, 0 };
	std::shared_ptr<Politician> en = std::make_shared<Politician>(attr, &textures[4], 0.25);
	en->setBodyTexture(&textures[0], 0.25);
	en->setGunTexture(&textures[1], 0.25, sf::Vector2f(-150, 0));
	en->setEnemyManager(this);
	en->setAmmoInfo(ami);
	en->setProjTexture(&textures[2], 0.25);
	en->setSpeed(25);
	en->enableArmor();
	en->initialize(getGame()->getMap()->getPath()->getStartSegment());
	en->setID(enemyIDCtr++);
	enemies.push_back(en);
}


void EnemyManager::spawnGoldRusher()
{
	Unit::Attributes attr = {
	50,  //current health
	10,   //damage
	0.5,  // fire rate
	250,  // range (in pixels)
	90,   //accuracy (0 to 100)
	500,   //projectile speed
	100,		//armor
	};
	Unit::AmmoInfo ami = {1,1};
	std::shared_ptr<GoldRusher> en = std::make_shared<GoldRusher>(attr);
	en->setBodyTexture(&textures[5], 0.25);
	en->setGunTexture(&textures[6], 0.25, sf::Vector2f(-100, 0));
	en->setEnemyManager(this);
	en->setAmmoInfo(ami);
	en->setSpeed(80);
	en->enableArmor();
	en->initialize(getGame()->getMap()->getPath()->getStartSegment());
	en->setID(enemyIDCtr++);
	enemies.push_back(en);
}