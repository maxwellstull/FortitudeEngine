#include "include/Path.h"

PathNode Path::getNextDestination(int idx)
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
	PathNode p0 = { std::make_shared<sf::Vector2f>(5 * scale, 217 * scale),
		PathNodeType::START };
	PathNode p1 = { std::make_shared<sf::Vector2f>(98 * scale, 217 * scale),
		PathNodeType::MIDPOINT};
	PathNode p2 = { std::make_shared<sf::Vector2f>(102 * scale, 102 * scale),
		PathNodeType::MIDPOINT };
	PathNode p3 = { std::make_shared<sf::Vector2f>(220 * scale, 102 * scale),
		PathNodeType::MIDPOINT };
	PathNode p4 = { std::make_shared<sf::Vector2f>(222 * scale, 257 * scale),
		PathNodeType::MIDPOINT };
	PathNode p5 = { std::make_shared<sf::Vector2f>(381 * scale, 257 * scale),
		PathNodeType::MIDPOINT };
	PathNode p6 = { std::make_shared<sf::Vector2f>(381 * scale, 182 * scale),
		PathNodeType::MIDPOINT };
	PathNode p7 = { std::make_shared<sf::Vector2f>(600 * scale, 182 * scale),
		PathNodeType::END };
	points.push_back(p0);
	points.push_back(p1);
	points.push_back(p2);
	points.push_back(p3);
	points.push_back(p4);
	points.push_back(p5);
	points.push_back(p6);
	points.push_back(p7);


	length = points.size();
}