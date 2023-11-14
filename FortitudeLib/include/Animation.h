#pragma once

#include <SFML/Graphics.hpp>



class Animation
{
private:
  double _startState;
  double _stopState;
  double _duration;
  double _elapsed;
  double _current;
  bool _active;
  bool _inversed;
  bool _shouldInverse;

public:
  bool isActive() { return _active; }
  double get() { return _current; }
  void update(double dt)
  {
    if(_active)
    {
      if (_inversed == false) //going up in value
      {
        _elapsed += dt;

        if (_elapsed >= _duration)
        {
          _current = _stopState;
          if (_shouldInverse)
          {
            _inversed = true;
            _elapsed = _duration;
          }
          else 
          {
            _active = false;
          }
        }
        else
        {
          // y(t) = ((y2 - y1)/(x2-x1))*t + y(0)
          _current = (((_stopState - _startState) / _duration) * _elapsed) + _startState;
        }
      }
      else //_inversed == true, going down in value
      {
        _elapsed -= dt;
        if (_elapsed <= _duration)
        {
          _active = false;
          _current = _startState;
        }
        else
        {
          _current = (((_stopState - _startState) / _duration) * _elapsed) + _startState;
        }
      }
    }
  }
  void activateForward() 
  {
    _elapsed = 0;
    _active = true;
    _inversed = false;
    _shouldInverse = false;
  }
  void activateReverse()
  {
    _elapsed = _duration;
    _active = true;
    _inversed = true;
    _shouldInverse = false;
  }
  void activate()
  {
    _elapsed = 0;
    _active = true;
    _inversed = false;
    _shouldInverse = true;
  }
  Animation(double start, double stop, double duration) : _startState(start), _stopState(stop), _duration(duration)
  {
    _elapsed = 0;
    _active = false;
    _inversed = false;
    _shouldInverse = false;
  }
};