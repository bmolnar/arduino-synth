#include "timer.h"

namespace synth {

Timer::Timer(duration_t period, TimerCallback callback)
    : period_(period), callback_(callback)
{
}
void Timer::Start()
{
  last_timestamp_ = micros();
  accum_ = 0;
}
void Timer::StepTo(timestamp_t timestamp)
{
  accum_ += timestamp - last_timestamp_;
  last_timestamp_ = timestamp;
  while (accum_ > period_) {
    if (callback_ != nullptr) {
      (*callback_)();
    }
    accum_ -= period_;
  }
}

} // namespace synth
