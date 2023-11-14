#include "include/Path.h"

std::shared_ptr<PathNode> Path::getNextDestination(int idx)
{
	if (idx >= length)
	{

	}
	return points[idx];
}

void Path::generatePath()
{
	points.clear();

	float scale = 2.7;
	std::shared_ptr<PathNode> p0 = std::make_shared<PathNode>();
	p0->location = sf::Vector2f(5 * scale, 217 * scale),
	p0->nodeType = PathNodeType::START;
	std::shared_ptr<PathNode> p1 = std::make_shared<PathNode>();
	p1->location = sf::Vector2f(98 * scale, 217 * scale),
	p1->nodeType = PathNodeType::MIDPOINT;
	std::shared_ptr<PathNode> p2 = std::make_shared<PathNode>();
	p2->location = sf::Vector2f(102 * scale, 102 * scale),
	p2->nodeType = PathNodeType::MIDPOINT;
	std::shared_ptr<PathNode> p3 = std::make_shared<PathNode>();
	p3->location = sf::Vector2f(220 * scale, 102 * scale),
	p3->nodeType = PathNodeType::MIDPOINT;
	std::shared_ptr<PathNode> p4 = std::make_shared<PathNode>();
	p4->location = sf::Vector2f(222 * scale, 257 * scale),
	p4->nodeType = PathNodeType::MIDPOINT;
	std::shared_ptr<PathNode> p5 = std::make_shared<PathNode>();
	p5->location = sf::Vector2f(381 * scale, 257 * scale),
	p5->nodeType = PathNodeType::MIDPOINT;
	std::shared_ptr<PathNode> p6 = std::make_shared<PathNode>();
	p6->location = sf::Vector2f(381 * scale, 182 * scale),
	p6->nodeType = PathNodeType::MIDPOINT;
	std::shared_ptr<PathNode> p7 = std::make_shared<PathNode>();
	p7->location = sf::Vector2f(600 * scale, 182 * scale),
	p7->nodeType = PathNodeType::MIDPOINT;
	std::shared_ptr<PathNode> p8 = std::make_shared<PathNode>();
	p8->location = sf::Vector2f(650 * scale, 182 * scale),
	p8->nodeType = PathNodeType::END;
	points.push_back(p0);
	points.push_back(p1);
	points.push_back(p2);
	points.push_back(p3);
	points.push_back(p4);
	points.push_back(p5);
	points.push_back(p6);
	points.push_back(p7);
	points.push_back(p8);
	

	length = points.size();
}