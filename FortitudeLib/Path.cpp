#include "include/Path.h"


bool doubleEQ(double d1, double d2)
{
	return fabs(d1 - d2) < 0.001;
}

void Path::generatePath()
{
	
	double scale = 2.7;
	double pathWidth = 20;
	double subSubmentSize = 40;

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
		sf::Vector2f(620 * scale, 182 * scale) };

	
	//generate the segments
	for (int i = 0; i < pts.size()-1; i++)
	{
		sf::Vector2f start = pts[i];
		sf::Vector2f end = pts[i + 1];

		double pathLength = sqrt(pow(end.y - start.y, 2) + pow(end.x - start.x, 2));
		double segmentAmnt = floor(pathLength / subSubmentSize);
		double pathHeading = atan2(end.y - start.y, end.x - start.x);
		double eachSegmentLength = pathLength / segmentAmnt;

		sf::Vector2f tmpStart = start;
		sf::Vector2f tmpEnd;
		for (int j = 0; j < segmentAmnt; j++)
		{
			PathSegment segment;

			tmpEnd.x = tmpStart.x + eachSegmentLength * cos(pathHeading);
			tmpEnd.y = tmpStart.y + eachSegmentLength * sin(pathHeading);

			segment.setSegmentStart(tmpStart);
			segment.setSegmentEnd(tmpEnd);
			segment.setSize(sf::Vector2f(pathWidth * 2, eachSegmentLength));

			//check x behavior
			if (doubleEQ(tmpStart.x, tmpEnd.x))
			{
				segment.ignoreX();
			}
			else if (tmpEnd.x > tmpStart.x)
			{
				segment.setXGreaterThan(true);
			}
			else
			{
				segment.setXGreaterThan(false);
			}

			if (doubleEQ(tmpStart.y, tmpEnd.y))
			{
				segment.ignoreY();
			}
			else if (tmpEnd.y > tmpStart.y)
			{
				segment.setYGreaterThan(true);
			}
			else
			{
				segment.setYGreaterThan(false);
			}



			if (i == 0 && j == 0)
			{
				segment.setNodeType(PathNodeType::START);
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
	segments[segments.size() - 1].setNodeType(PathNodeType::END);


}

void Path::Draw(sf::RenderWindow* context)
{
	for (auto seg : segments)
	{
		seg.draw(context);
	}
}
