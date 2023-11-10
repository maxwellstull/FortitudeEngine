#include "include/Map.h"

Map::Map(const char* mapname, const char* title)
{
	tex.loadFromFile(mapname);
	spr.setTexture(tex);
	name = title;
}
Map::Map(const char * mapname, const char* title, sf::IntRect rec)
{
	tex.loadFromFile(mapname, rec);
	spr.setTexture(tex);
}

void Map::Draw(sf::RenderWindow * context)
{
	context->draw(spr);
}