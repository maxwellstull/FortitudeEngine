#include "include/Game.h"

void Game::update(float dtAsSeconds)
{
	if(isActive)
	{
		enm.update(dtAsSeconds);
	}
}


void Game::load()
{
	enm.setGame(this);
	enm.initialize(info);





	activate();
}

void Game::Draw(sf::RenderWindow* context)
{
	activeMap->Draw(context);
	enm.Draw(context);
}