#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include "GameStructures.h"

class Enemy;

class PathSegment
{
private:
  sf::Vector2f _start;
  sf::Vector2f _end;
  sf::Vector2f _size;
  
  bool _xGreaterThan;
  bool _yGreaterThan;

  PathNodeType _type;
  
  PathSegment* _next;
  PathSegment* _prev;

  //std::vector<Enemy*> _contained;
  std::map<int, Enemy*> _contained;


//  std::vector<sf::Vector2f> _leftEdge;
//  std::vector<sf::Vector2f> _rightEdge;
//  std::vector<sf::Vector2f> _centerPath;

public:
  PathSegment() {};
  void setSegmentStart(sf::Vector2f start) { _start = start; }
  sf::Vector2f getSegmentStart() { return _start; }
  void setSegmentEnd(sf::Vector2f end) { _end = end; }
  sf::Vector2f getSegmentEnd() { return _end; }
  void setNodeType(PathNodeType tp) { _type = tp; }
  PathNodeType getNodeType() { return _type; }

  void setSize(sf::Vector2f sz) { _size = sz; }
  double getLength() { return _size.y; }
  void setNext(PathSegment* seg) { _next = seg; }
  PathSegment* getNext() { return _next; }
  void setPrev(PathSegment* seg) { _prev = seg; }
  PathSegment* getPrev() { return _prev; }
  void setXGreaterThan(bool t) { _xGreaterThan = t; }
  void setYGreaterThan(bool t) { _yGreaterThan = t; }
  bool contains(sf::Vector2f check);
  void remove(int idx);
  void add(Enemy* en);

//  std::map<int, Enemy*>* getContained() { return &_contained; }
  std::vector<Enemy*> getContained();

};