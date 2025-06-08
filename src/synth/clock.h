#ifndef SYNTH__CLOCK_H_
#define SYNTH__CLOCK_H_

#include "types.h"

namespace synth {

class Clock
{
public:
  Clock();

  /**
   * Resets and starts the clock
   */
  void Start();

  /**
   * Gets current value of timer
   *
   * @return Elapsed time in microseconds
   */
  timestamp_t Now();

protected:
  timestamp_t start_{0};
  unsigned long count_{0};
};

} // namespace synth

#endif // SYNTH__CLOCK_H_
