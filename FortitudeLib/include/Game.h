#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "GameStructures.h"

class Engine;

class Game
{
private:
	struct GameState {
		int maxHealth;
		int currentHealth;
	};
	bool isActive;
	Engine* engine = nullptr;
	std::shared_ptr<Map> activeMap;
	EnemyManager enm;
	GameInfo info;
	int waveCt;
	GameState state;


	// money bag
	sf::Font font;
	sf::Texture moneyTex;
	sf::Sprite moneySpr;
	sf::Text healthHUD;

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
	void updateHealthHUD();
	void decrementCurrentHealth(int amnt = 1) { state.currentHealth -= amnt; updateHealthHUD(); }
};