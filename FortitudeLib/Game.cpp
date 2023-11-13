#include "include/Game.h"

void Game::update(float dtAsSeconds)
{
	if(isActive)
	{
		for (Enemy en : enemies)
		{
			en.update(dtAsSeconds);
		}
	}
}


void Game::load()
{

}

void Game::Draw(sf::RenderWindow* context)
{

}