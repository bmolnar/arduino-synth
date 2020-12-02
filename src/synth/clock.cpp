#include "clock.h"

namespace synth {

Clock::Clock()
{
}
void Clock::Start()
{
  count_ = 0;
}
timestamp_t Clock::Now()
{
  timestamp_t now = micros();
  if (count_++ == 0) {
    start_ = now;
  }
  return now - start_;
}

} // namespace synth
