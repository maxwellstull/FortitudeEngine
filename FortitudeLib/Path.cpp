#include "include/Path.h"

void Path::generatePath()
{
	float scale = 2.7;
	std::shared_ptr<sf::Vector2f> p0 = std::make_shared<sf::Vector2f>(5 * scale, 217 * scale);
	std::shared_ptr<sf::Vector2f> p1 = std::make_shared<sf::Vector2f>(98 * scale, 217 * scale);
	std::shared_ptr<sf::Vector2f> p2 = std::make_shared<sf::Vector2f>(102 * scale, 102 * scale);
	std::shared_ptr<sf::Vector2f> p3 = std::make_shared<sf::Vector2f>(220 * scale, 102 * scale);
	std::shared_ptr<sf::Vector2f> p4 = std::make_shared<sf::Vector2f>(222 * scale, 257 * scale);
	std::shared_ptr<sf::Vector2f> p5 = std::make_shared<sf::Vector2f>(381 * scale, 257 * scale);
	std::shared_ptr<sf::Vector2f> p6 = std::make_shared<sf::Vector2f>(381 * scale, 182 * scale);
	std::shared_ptr<sf::Vector2f> p7 = std::make_shared<sf::Vector2f>(600 * scale, 182 * scale);
	points.push_back(p0);
	points.push_back(p1);
	points.push_back(p2);
	points.push_back(p3);
	points.push_back(p4);
	points.push_back(p5);
	points.push_back(p6);
	points.push_back(p7);
}