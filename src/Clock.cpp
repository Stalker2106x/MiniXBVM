#include "Clock.hh"
#include <thread>

Clock::Clock()
{
  _frequency = 1; //Hertz
}

bool Clock::cycle(int deltaTime)
{
  _timeAccumulated += deltaTime;
  if (_timeAccumulated > 1000/_frequency)
  {
    _timeAccumulated = 0;
    return (true);
  }
  return (false);
}