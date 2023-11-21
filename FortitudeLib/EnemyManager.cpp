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
	Unit::Attributes attr = { 100, 100, 10, 0.2, 300, 80 };
	std::shared_ptr<Enemy> en = std::make_shared<Enemy>(attr);
	en->setBodyTexture(&textures[0], 0.25);
	en->setGunTexture(&textures[1], 0.25, sf::Vector2f(-150, 0));
	en->setEnemyManager(this);
	en->setProjTexture(&textures[2], 0.25);
	en->setSpeed(50);
	en->initialize(getGame()->getMap()->getPath()->getStartSegment());
	en->setID(enemyIDCtr++);
	enemies.push_back(en);
}


