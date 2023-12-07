#include "include/Map.h"

Map::Map(const char* mapname, const char* title)
{
	tex.loadFromFile(mapname);
	spr.setTexture(tex);
	name = title;
	_initialized = false;
}
Map::Map(const char * mapname, const char* title, sf::IntRect rec)
{
	tex.loadFromFile(mapname, rec);
	spr.setTexture(tex);
	_initialized = false;
}

void Map::Draw(sf::RenderWindow * context)
{
	context->draw(spr);
	if(_initialized)
	{
		path.Draw(context);
	}
}

void Map::initialize()
{
	path.generatePath();
	_initialized = true;
}