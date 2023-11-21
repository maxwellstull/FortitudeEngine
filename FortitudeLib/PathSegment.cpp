#define _USE_MATH_DEFINES
#include "include/PathSegment.h"
#include <cmath>
#include "include/Enemy.h"


bool PathSegment::contains(sf::Vector2f check)
{
  bool retVal = false;
  if (_xGreaterThan == true && _yGreaterThan == true) //down right
  {
    if (check.x > _end.x || check.y > _end.y)
    {
      retVal = true;
    }
  }
  else if (_xGreaterThan == false && _yGreaterThan == true) //down left
  {
    if (check.x < _end.x || check.y > _end.y)
    {
      retVal = true;
    }
  }
  else if (_xGreaterThan == false && _yGreaterThan == false) //up left
  {
    if (check.x < _end.x || check.y < _end.y)
    {
      retVal = true;
    }
  }
  else if (_xGreaterThan == true && _yGreaterThan == false) //up right
  {
    if (check.x > _end.x || check.y < _end.y)
    {
      retVal = true;
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

std::vector<Enemy*> PathSegment::getContained()
{
  std::vector<Enemy*> retVal;

  for (auto en : _contained)
  {
    retVal.push_back(en.second);
  }

  return retVal;
}