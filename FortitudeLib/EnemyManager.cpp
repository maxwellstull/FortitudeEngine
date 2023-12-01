#include "include/EnemyManager.h"
#include "include/Game.h"

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

	enemyIDCtr = 0;

	spawnBadGuy();
}

void EnemyManager::Draw(sf::RenderWindow* context)
{
	for (std::shared_ptr<Unit> en : enemies)
	{
		en->draw(context);
	}
}

void EnemyManager::spawnBadGuy() 
{
	Unit::Attributes attr = { 
    100,  //max health
    100,  //current health
    2,   //damage
    1,  // fire rate
    300,  // range (in pixels)
    80,   //accuracy (0 to 100)
    500   //projectile speed
  };
	Unit::AmmoInfo ami = { 6, 6 };
	std::shared_ptr<Enemy> en = std::make_shared<Enemy>(attr);
	en->setBodyTexture(&textures[0], 0.25);
	en->setGunTexture(&textures[1], 0.25, sf::Vector2f(-150, 0));
	en->setEnemyManager(this);
	en->setAmmoInfo(ami);
	en->setProjTexture(&textures[2], 0.25);
	en->setSpeed(50);
	en->initialize(getGame()->getMap()->getPath()->getStartSegment());
	en->setID(enemyIDCtr++);
	enemies.push_back(en);
}


