#include "Clock.hh"
#include <thread>

Clock::Clock()
{
  _frequency = 1; //Hertz
}

void Clock::cycle()
{
  std::this_thread::sleep_for(std::chrono::seconds(1/_frequency));
}