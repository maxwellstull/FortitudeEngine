#include "include/EnemyManager.h"
#include "include/Game.h"

void EnemyManager::update(float dtAsSeconds)
{
	for (std::shared_ptr<Enemy> en : enemies)
	{
		en->update(dtAsSeconds);
	}
}

void EnemyManager::initialize(GameInfo info)
{
	//load textures
	sf::Texture texture;
	texture.loadFromFile("img/baddy.png");
	textures.push_back(texture);


	std::shared_ptr<Enemy> en = std::make_shared<Enemy>();
	en->setTexture(&textures[0]);
	en->setEnemyManager(this);
	en->setSpeed(50);
	en->initialize(*getGame()->getMap()->getPath()->getNextDestination(0));
//	en->setDestination(getGame()->getMap()->getPath()->getNextDestination(1));
	
	enemies.push_back(en);
}

void EnemyManager::Draw(sf::RenderWindow* context)
{
	for (std::shared_ptr<Enemy> en : enemies)
	{
		en->Draw(context);
	}
}


