#include "Clock.hh"
#include <thread>

Clock::Clock()
{
  _state = Paused;
  _tick = 0;
  _frequency = 1; //Hertz
}

size_t Clock::getTick()
{
  return (_tick);
}

Clock::State Clock::getState()
{
  return (_state);
}

void Clock::toggle()
{
  _state = (_state == Running ? Paused : Running);
  _timeAccumulated = 0;
}

void Clock::nextStep()
{
  _state = NextStep;
  _timeAccumulated = 1000/_frequency;
}

bool Clock::cycle(int deltaTime)
{
  if (_state == Paused) return (false);
  _timeAccumulated += deltaTime;
  if (_timeAccumulated >= 1000/_frequency)
  {
    if (_state == NextStep) _state = Paused; //Stepped forward, now pause.
    _timeAccumulated = 0;
    ++_tick;
    return (true);
  }
  return (false);
}