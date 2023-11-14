#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "GameInfo.h"

class Engine;

class Game
{
private:
	bool isActive;
	Engine* engine = nullptr;
	std::shared_ptr<Map> activeMap;
	EnemyManager enm;
	//vector of towers
//	std::vector<Enemy> enemies;
	GameInfo info;
	int waveCt;

public:
	void activate() { isActive = true; }
	void deactivate() { isActive = false; }
	int getWaveCt() { return waveCt; }
	void setWaveCt(int wavs) { waveCt = wavs; }
	void SetEngine(Engine* e) { engine = e; }
	Engine* GetEngine() { return engine; }
	void update(float dtAsSeconds);
	std::shared_ptr<Map> getMap() { return activeMap; }
	void setMap(std::shared_ptr<Map> map) { activeMap = map; }
	void load();
	void Draw(sf::RenderWindow* context);
};