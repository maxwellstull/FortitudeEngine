#pragma once
struct GameInfo {
	int MaxWaves;
	int Difficulty;
	int WaveNum;
};

enum PathNodeType {
	START = 0,
	MIDPOINT = 1,
	END = 2,
};

struct PathNode {
	std::shared_ptr<sf::Vector2f> location;
	PathNodeType nodeType;
};