#pragma once
#include <SFML/Graphics.hpp>
#include "GameStructures.h"
#include <vector>



class Path {
private:
	std::vector<std::shared_ptr<PathNode>> points;
	int length;
public:
	std::shared_ptr<PathNode> getNextDestination(int idx);
	void generatePath();

};