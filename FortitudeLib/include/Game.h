#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Enemy.h"

class Engine;

class Game
{
public:
	struct GameInfo {
		int MaxWaves;
		int Difficulty;
		int WaveNum;
	};
private:
	bool isActive;
	Engine* engine = nullptr;
	std::shared_ptr<Map> activeMap;
	//vector of towers
	std::vector<Enemy> enemies;
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