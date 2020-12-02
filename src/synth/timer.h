#ifndef SYNTH__TIMER_H_
#define SYNTH__TIMER_H_

#include "types.h"

namespace synth {

typedef void (*TimerCallback)(void);

class Timer
{
public:
  Timer(duration_t period, TimerCallback callback);
  void Start();
  void StepTo(timestamp_t timestamp);

protected:
  duration_t period_;
  TimerCallback callback_;
  timestamp_t last_timestamp_{0};
  duration_t accum_{0};
};

} // namespace synth

#endif // SYNTH__TIMER_H_
