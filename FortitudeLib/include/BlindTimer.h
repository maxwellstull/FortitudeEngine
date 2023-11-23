#pragma once
#include <functional>

/*
 * Blind timer is a timer that does not wait to be perceived in order
 * to continue operation. It is made specifically with status effects in mind
 * (though I have no doubt I'll find a way to cheese it and use it elsewhere).
 * The main feature is the ability to run a function on completion (or loop). 
 * So, it can be a timer that is created to last for 5 seconds when a unit gets
 * blinded, and then when the 5 seconds is up, it will automatically run the command
 * to clear the blinded status effect. 
 * It can also be used to loop, such as bleeding damage. A unit might take 1hp of bleeding
 * damage every second for 5 seconds. So, we can set the timer to loop 5 times and
 * at each loop run a function that subtracts 1 health from the unit. 
 * The key details is that this timer is "headless", it's not meant
 * to be read. The reading should be to check if its done with everything
 * it's meant to do, in which case it should tell whoever owns it to delete it.
*/
class BlindTimer
{
private:
	double _period;
	double _timer;
	bool _completed;

	int _loopCt;
	std::function<void()> _onLoop;
	bool _doOnLoop;

	std::function<void()> _onComplete;
	bool _doOnComplete;

	bool _shouldDoLoopFuncOnComplete;
public:
	BlindTimer() {};
	BlindTimer(double period) : _period(period)
	{
		_timer = period;
		_completed = false;
		_loopCt = 0;
		_doOnLoop = false;
		_doOnComplete = false;
		_shouldDoLoopFuncOnComplete = false;
	}
	BlindTimer(double period, double reps) : _period(period), _loopCt(reps)
	{
		_timer = period;
		_completed = false;
		_doOnLoop = false;
		_doOnComplete = false;
		_shouldDoLoopFuncOnComplete = false;
	}
	void setOnLoopFunction(std::function<void()> func)
	{
		_onLoop = func;
		_doOnLoop = false;
	}
	void setOnCompleteFunction(std::function<void()> func)
	{
		_onComplete = func;
		_doOnComplete = true;
	}
	void setDoLoopFuncOnComplete()
	{
		_shouldDoLoopFuncOnComplete = true;
	}
	void update(double dt)
	{
		_timer -= dt;
		if (_timer <= 0)	//Timer under 0, loop or end
		{
			if (_loopCt == 0)	//out of loops, end
			{
				if(_doOnComplete)
				{
					if (_shouldDoLoopFuncOnComplete)
					{
						_onLoop();
					}
					_onComplete();
				}
				_completed = true;
			}
			else		//Run loop command if wanted, reset timer to loop
			{
				if (_doOnLoop)
				{
					_onLoop();
				}
				_timer = _period;
				_loopCt -= 1;
			}
		}
	}
	bool isDone() { return _completed; }
};