//#include "stdafx.h"
#include "include/Engine.h"


void Engine::update(float dtAsSeconds)
{
	menu.update(dtAsSeconds);
	game.update(dtAsSeconds);
}