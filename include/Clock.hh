#ifndef CLOCK_HH_
#define CLOCK_HH_

#include <cstddef>
#include <vector>

class Clock
{
public:
  enum State {
    Paused,
    Running,
    NextStep,
  };

  Clock();
  unsigned int getFrequency();
  void setFrequency(unsigned int value);
  size_t getTick();
  State getState();
  void reset();
  const float *getHistoryData();
  void setState(Clock::State state);
  void toggle();
  void nextStep();
  bool cycle(int deltaTime);

private:
  State _state;
  size_t _tick;
  std::vector<float> _historyData;
  unsigned int _clockTimer;
  unsigned int _dataTimer;
  unsigned int _frequency;
};

#endif /* !CLOCK_HH_ */