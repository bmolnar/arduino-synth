#ifndef SYNTH__TIMER_H_
#define SYNTH__TIMER_H_

#include "types.h"

namespace synth {

typedef void (*TimerCallback)(void);

class Timer
{
public:
  /**
   * Initializes timer that periodically calls a callback
   *
   * @param period Duration between callbacks
   * @param Function to be called each interval
   */
  Timer(duration_t period, TimerCallback callback);

  /**
   * Starts the timer
   */
  void Start();

  /**
   * Advances timer to given time
   *
   * @param timestamp Current time
   */
  void StepTo(timestamp_t timestamp);

protected:
  duration_t period_;
  TimerCallback callback_;
  timestamp_t last_timestamp_{0};
  duration_t accum_{0};
};

} // namespace synth

#endif // SYNTH__TIMER_H_
