#pragma once
#include <functional>

class Timer {
private:
  // Secs/cycle
  double _period;
  // Thing that counts down to 0, gets reset to _period
  double _timer;
  // If timer has hit 0 and is waiting for a reset
  bool _primed;

  std::function<void()> _onComplete;
  bool _doOnComplete;

public:
  Timer() {};
  Timer(double period) : _period(period)
  {
    _timer = period;
    _primed = false;
  }
  void update(double dt)
  {
    if (_primed == false)
    {
      _timer -= dt;
      if (_timer <= 0)
      {
        _primed = true;
      }
    }
  };
  void clear() { _timer = _period; _primed = false; }
  /*
  * Getting the timer will reset it and it will begin counting again.
  */
  bool get()
  {
    if (_primed == true) 
    {
      _primed = false;
      _timer = _period;
      return true;
    }
    else
    {
      return false;
    }
  }
  void setOnCompleteFunction(std::function<void()> func)
  {
      _onComplete = func;
      _doOnComplete = true;
  }
};