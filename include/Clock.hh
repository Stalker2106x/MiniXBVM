#ifndef CLOCK_HH_
#define CLOCK_HH_

class Clock
{
public:
  Clock();
  bool cycle(int deltaTime);

private:
  unsigned int _timeAccumulated;
  unsigned int _frequency;
};

#endif /* !CLOCK_HH_ */