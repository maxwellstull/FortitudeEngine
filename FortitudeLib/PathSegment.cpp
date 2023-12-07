#define _USE_MATH_DEFINES
#include "include/PathSegment.h"
#include <cmath>
#include "include/Enemy.h"


bool PathSegment::contains(sf::Vector2f check)
{
  bool retVal = false;

  if (_ignoreX == false)
  {
      if (_xGreaterThan == true)
      {
          if (check.x > _end.x)
          {
              retVal = true;
          }
      }
      else
      {
          if (check.x < _end.x)
          {
              retVal = true;
          }
      }
  }
  if (_ignoreY == false)
  {
      if (_yGreaterThan == true)
      {
          if (check.y > _end.y)
          {
              retVal = true;
          }
      }
      else
      {
          if (check.y < _end.y)
          {
              retVal = true;
          }
      }
  }
  return retVal;
}

void PathSegment::remove(int idx)
{
  _contained.erase(idx);
}
void PathSegment::add(Enemy* en)
{
  _contained[en->getID()] = en;
}

void PathSegment::draw(sf::RenderWindow* context)
{
    sf::Vertex line[] = {
        sf::Vertex(_start),
        sf::Vertex(_end),
    };
    sf::CircleShape circle1(2);
    sf::CircleShape circle2(2);
    sf::FloatRect bds = circle1.getLocalBounds();
    circle1.setOrigin(bds.left + (bds.width / 2.f), bds.top + (bds.height / 2.f));
    bds = circle2.getLocalBounds();
    circle2.setOrigin(bds.left + (bds.width / 2.f), bds.top + (bds.height / 2.f));
    circle1.setPosition(_start);
    circle2.setPosition(_end);
    context->draw(line, 2, sf::Lines);
    context->draw(circle1);
    context->draw(circle2);
}

std::vector<Enemy*> PathSegment::getContained()
{
  std::vector<Enemy*> retVal;

  for (auto en : _contained)
  {
    retVal.push_back(en.second);
  }

  return retVal;
}