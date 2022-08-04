#include "Clock.hh"
#include <algorithm>

Clock::Clock()
: _state(Paused), _tick(0), _frequency(1/* Hz */), _historyData(200, 0.0f)
{
}

size_t Clock::getTick()
{
  return (_tick);
}

unsigned int Clock::getFrequency()
{
  return (_frequency);
}

void Clock::setFrequency(unsigned int value)
{
  _frequency = value;
}

Clock::State Clock::getState()
{
  return (_state);
}

void Clock::reset()
{
  _tick = 0;
  _clockTimer = 0;
  _historyData.clear();
}

const float *Clock::getHistoryData()
{
  return (&_historyData[0]);
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
  bool trigged = false;
  if (_state == Paused || _frequency == 0) return (false);
  _clockTimer += deltaTime;
  if (_clockTimer >= 1000/_frequency)
  {
    if (_state == NextStep) _state = Paused; //Stepped forward, now pause.
    _clockTimer = 0;
    ++_tick;
    trigged = true;
  }

  _dataTimer += deltaTime;
  if (_dataTimer >= 1)
  {
    _historyData[0] = (trigged ? 1.0f : 0.0f);
    std::rotate(_historyData.begin(), _historyData.begin() + 1, _historyData.end());
    _dataTimer = 0; //reset ctr
  }
  return (trigged);
}