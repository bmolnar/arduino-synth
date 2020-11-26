#ifndef SYNTH__TIMER_H_
#define SYNTH__TIMER_H_

#include "types.h"

namespace synth {

class Timer
{
public:
  Timer();
  void Start();
  duration_t ElapsedSinceLast();
protected:
  duration_t last_usec_;
};

} // namespace synth

#endif // SYNTH__TIMER_H_
