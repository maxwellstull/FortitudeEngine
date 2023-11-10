#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"

class Engine;

class Game
{
public:
	
private:
	Engine* engine = nullptr;
	std::shared_ptr<Map> activeMap;
	//vector of towers
	//vector of enemies
	int waveCt;

public:
	int getWaveCt() { return waveCt; }
	void setWaveCt(int wavs) { waveCt = wavs; }
	void SetEngine(Engine* e) { engine = e; }
	Engine* GetEngine() { return engine; }
};