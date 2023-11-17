#pragma once
#include <SFML/Graphics.hpp>
#include "GameStructures.h"
#include <vector>
#include "PathSegment.h"


class Path {
private:
	std::vector<PathSegment> segments;
	int length;
public:
	PathSegment* getSegment(int idx) { return &segments[idx];}
	void generatePath();
	PathSegment* getStartSegment() { return getSegment(0); }

};