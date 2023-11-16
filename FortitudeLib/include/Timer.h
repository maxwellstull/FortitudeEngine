#pragma once


class Timer {
private:
  // Secs/cycle
  double _period;
  // Thing that counts down to 0, gets reset to _period
  double _timer;
  // If timer is active
  bool _active;
  // If timer has hit 0 and is waiting for a reset
  bool _primed;

public:
  Timer(double period) : _period(period)
  {
    _timer = period;
    _active = false;
    _primed = false;
  }
  void update(double dt)
  {
    if (_active == true)
    {
      _timer -= dt;
      if (_timer <= 0)
      {
        _primed = true;
        _active = false;
      }
    }
  };
  /*
  * Getting the timer will reset it and it will begin counting again.
  */
  bool get()
  {
    if (_primed == true) 
    {
      _primed = false;
      _active = true;
      _timer = _period;
      return true;
    }
    else
    {
      return false;
    }
  }
};