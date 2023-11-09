#include "include/Map.h"


void Map::init(const char * mapname, const char* title)
{
	tex.loadFromFile(mapname);
	spr.setTexture(tex);
	name = title;
}

void Map::Draw(sf::RenderWindow * context)
{
	context->draw(spr);
}