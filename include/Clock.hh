#ifndef CLOCK_HH_
#define CLOCK_HH_

#include <iostream>

class Clock
{
public:
  enum State {
    Paused,
    Running,
    NextStep,
  };

  Clock();
  size_t getTick();
  State getState();
  void toggle();
  void nextStep();
  bool cycle(int deltaTime);

private:
  State _state;
  size_t _tick;
  unsigned int _timeAccumulated;
  unsigned int _frequency;
};

#endif /* !CLOCK_HH_ */