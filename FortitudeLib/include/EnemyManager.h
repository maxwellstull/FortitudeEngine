#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include <vector>
#include <memory>
#include "GameStructures.h"

#include "Unit.h"

class Game;

class EnemyManager
{
private:
	int enemyIDCtr;
	Game* game;
	std::vector<std::shared_ptr<Enemy>> enemies;
	std::vector<sf::Texture> textures;
public:
	void update(float dtAsSeconds);
	void initialize(GameInfo info);
	Game* getGame() { return game; }
	void setGame(Game* g) { game = g; }
	void Draw(sf::RenderWindow* context);
	std::vector<std::shared_ptr<Enemy>> getEnemies() { return enemies; }
	void spawnBadGuy();
	void spawnTrainRobber();
	void spawnPolitician();
	void spawnGoldRusher();
};