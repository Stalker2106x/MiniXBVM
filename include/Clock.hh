#ifndef CLOCK_HH_
#define CLOCK_HH_

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
  const float *getHistoryData();
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