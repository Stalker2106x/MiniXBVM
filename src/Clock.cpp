#include "Clock.hh"
#include <algorithm>

Clock::Clock()
: _state(Paused), _tick(0), _frequency(1/* Hz */)
{
}

size_t Clock::getTick() const
{
  return (_tick);
}

unsigned int Clock::getFrequency() const
{
  return (_frequency);
}

void Clock::setFrequency(unsigned int value)
{
  _frequency = value;
}

const bool Clock::isTickTriggered() const
{
  return (_tickTriggered);
}

Clock::State Clock::getState() const
{
  return (_state);
}

void Clock::reset()
{
  _tick = 0;
  _clockTimer = 0;
}

void Clock::setState(Clock::State state)
{
  _state = state;
  _clockTimer = 0;
}

void Clock::toggle()
{
  setState(_state == Running ? Paused : Running);
}

void Clock::nextStep()
{
  _state = NextStep;
  _clockTimer = 1000/_frequency;
}

bool Clock::cycle(int deltaTime)
{
  _tickTriggered = false;
  if (_state == Paused || _frequency == 0) return (_tickTriggered);
  _clockTimer += deltaTime;
  if (_clockTimer >= 1000/_frequency)
  {
    if (_state == NextStep) _state = Paused; //Stepped forward, now pause.
    _clockTimer = 0;
    ++_tick;
    _tickTriggered = true;
  }

  _dataTimer += deltaTime;
  if (_dataTimer >= 1)
  {
    _dataTimer = 0; //reset ctr
  }
  return (_tickTriggered);
}