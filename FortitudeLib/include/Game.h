#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "GameStructures.h"
#include "TowerManager.h"

class Engine;

class Game
{
private:
	struct GameState {
		int maxHealth;
		int currentHealth;
		int currentWave;
	};
	bool isActive;
	Engine* engine = nullptr;
	std::shared_ptr<Map> activeMap;
	EnemyManager enm;
	TowerManager twm;
	GameInfo info;
	GameState state;


	// money bag
	sf::Font font;
	sf::Texture moneyTex;
	sf::Sprite moneySpr;
	sf::Text healthHUD;

	// wave ctr
	sf::Texture waveTex;
	sf::Sprite waveSpr;
	sf::Text waveHUD;

public:
	void activate() { isActive = true; }
	void deactivate() { isActive = false; }
	int getWaveCt() { return info.MaxWaves; }
	void setWaveCt(int wavs) { info.MaxWaves = wavs; }
	void SetEngine(Engine* e) { engine = e; }
	Engine* GetEngine() { return engine; }
	void update(float dtAsSeconds);
	std::shared_ptr<Map> getMap() { return activeMap; }
	void setMap(std::shared_ptr<Map> map) { activeMap = map; }
	TowerManager* getTowerManager() { return &twm; }
	EnemyManager* getEnemyManager() { return &enm; }
	void load();
	void Draw(sf::RenderWindow* context);
	void updateHealthHUD();
	void updateWaveHUD();
	void incrementWave(int amnt = 1 ) { }
	void decrementCurrentHealth(int amnt = 1) { state.currentHealth -= amnt; updateHealthHUD(); }
	sf::Texture* getTowerTexture(int idx) { return twm.getTowerTexture(idx); }
};