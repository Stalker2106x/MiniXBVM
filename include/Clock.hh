#ifndef CLOCK_HH_
#define CLOCK_HH_

class Clock
{
public:
  Clock();
  void cycle();

private:
  unsigned int _frequency;
};

#endif /* !CLOCK_HH_ */