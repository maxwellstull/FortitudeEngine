#include "include/Map.h"

Map::Map(const char* mapname, const char* title)
{
	tex.loadFromFile(mapname);
	spr.setTexture(tex);
	name = title;
	path.generatePath();
}
Map::Map(const char * mapname, const char* title, sf::IntRect rec)
{
	tex.loadFromFile(mapname, rec);
	spr.setTexture(tex);
	path.generatePath();
}

void Map::Draw(sf::RenderWindow * context)
{
	context->draw(spr);
}