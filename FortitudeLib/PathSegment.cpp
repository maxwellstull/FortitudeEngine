#define _USE_MATH_DEFINES
#include "include/PathSegment.h"
#include <cmath>

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
