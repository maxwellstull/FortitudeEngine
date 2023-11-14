#pragma once
struct GameInfo {
	int MaxWaves;
	int Difficulty;
	int StartingHealth;
};

enum PathNodeType {
	START = 0,
	MIDPOINT = 1,
	END = 2,
};

struct PathNode {
	sf::Vector2f location;
	PathNodeType nodeType;
};