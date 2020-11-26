#include "timer.h"

namespace synth {

Timer::Timer()
{
  last_usec_ = micros();
}
void Timer::Start()
{
  last_usec_ = micros();
}
duration_t Timer::ElapsedSinceLast()
{
  duration_t now = micros();
  duration_t result = now - last_usec_;
  last_usec_ = now;
  return result;
}

} // namespace synth
