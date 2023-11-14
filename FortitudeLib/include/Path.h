#pragma once
#include <SFML/Graphics.hpp>
#include "GameStructures.h"
#include <vector>



class Path {
private:
	std::vector<PathNode> points;
	int length;
public:
	PathNode getNextDestination(int idx);
	void generatePath();

};