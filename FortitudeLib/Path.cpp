#include "include/Path.h"


void Path::generatePath()
{
	
	double scale = 2.7;
	double pathWidth = 20;
	double subSubmentSize = 20;

	std::vector<sf::Vector2f> pts = {
		sf::Vector2f(0 * scale, 221 * scale),
		sf::Vector2f(81 * scale, 221 * scale),
		sf::Vector2f(100 * scale, 201 * scale),
		sf::Vector2f(100 * scale, 120 * scale),
		sf::Vector2f(120 * scale, 98 * scale),
		sf::Vector2f(199 * scale, 98 * scale),
		sf::Vector2f(220 * scale, 120 * scale),
		sf::Vector2f(220 * scale, 241 * scale),
		sf::Vector2f(240 * scale, 260 * scale),
		sf::Vector2f(359 * scale, 260 * scale),
		sf::Vector2f(379 * scale, 241 * scale),
		sf::Vector2f(379 * scale, 199 * scale),
		sf::Vector2f(400 * scale, 180 * scale),
		sf::Vector2f(600 * scale, 180 * scale),
		sf::Vector2f(650 * scale, 182 * scale) };

	//generate the segments
	for (int i = 0; i < pts.size() - 1; i++)
	{
		sf::Vector2f start = pts[i];
		sf::Vector2f end = pts[i + 1];

		double pathLength = sqrt(pow(end.y - start.y, 2) + pow(end.x - start.x, 2));
		double segmentAmnt = floor(pathLength / subSubmentSize);
		double pathHeading = atan2(end.y - start.y, end.x - start.x);
		double eachSegmentLength = pathLength / segmentAmnt;

		sf::Vector2f tmpStart = start;
		sf::Vector2f tmpEnd;
		for (int i = 0; i < segmentAmnt; i++)
		{
			PathSegment segment;

			tmpEnd.x = tmpStart.x + eachSegmentLength * cos(pathHeading);
			tmpEnd.y = tmpStart.y + eachSegmentLength * sin(pathHeading);

			segment.setSegmentStart(tmpStart);
			segment.setSegmentEnd(tmpEnd);
			segment.setSize(sf::Vector2f(pathWidth * 2, eachSegmentLength));

			if (tmpEnd.x > tmpStart.x && tmpEnd.y > tmpStart.y) //down-right
			{
				segment.setXGreaterThan(true);
				segment.setYGreaterThan(true);
			}
			else if (tmpEnd.x < tmpStart.x && tmpEnd.y > tmpStart.y) //down-left
			{
				segment.setXGreaterThan(false);
				segment.setYGreaterThan(true);
			}
			else if (tmpEnd.x < tmpStart.x && tmpEnd.y < tmpStart.y) //up-left
			{
				segment.setXGreaterThan(false);
				segment.setYGreaterThan(false);
			}
			else if (tmpEnd.x > tmpStart.x && tmpEnd.y < tmpStart.y) //up-right
			{
				segment.setXGreaterThan(true);
				segment.setYGreaterThan(false);
			}


			if (i == 0)
			{
				segment.setNodeType(PathNodeType::START);
			}
			else if (i == (pts.size() - 1))
			{
				segment.setNodeType(PathNodeType::END);
			}
			else
			{
				segment.setNodeType(PathNodeType::MIDPOINT);
			}

			
			segments.push_back(segment);
			tmpStart = tmpEnd;
		}
	}
	//Link nodes
	for (int i = 0; i < segments.size() - 1; i++)
	{
		segments[i].setNext(&segments[i + 1]);
		segments[i + 1].setPrev(&segments[i]);
	}


}