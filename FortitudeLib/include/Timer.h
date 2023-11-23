#pragma once
#include <functional>


/*
 * Timer is a basic timer that allows for simple timing. The timer will
 * continuously count down until it hits zero, and will then be "primed".
 * Once primed, it will not count down anymore, and will return 'true' 
 * the next time get() is called on it. After that, it will start over.
 * 
 * In essence, it's an egg timer. In order for it to count again,
 * you have to wind it up. In this case, you wind it up by reading its state.
*/
class Timer {
private:
  // Secs/cycle
  double _period;
  // Thing that counts down to 0, gets reset to _period
  double _timer;
  // If timer has hit 0 and is waiting for a reset
  bool _primed;
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
  void setReady()
  {
      _primed = true;
      _timer = 0;
  }
  double DEBUGget()
  {
      return _timer;
  }
};