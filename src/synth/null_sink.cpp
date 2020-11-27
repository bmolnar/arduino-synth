#include "null_sink.h"

namespace synth {

NullSink::NullSink(SignalSource& source0)
  : source0_(source0)
{
}


void NullSink::StepPre(duration_t delta_t)
{
  source0_.Owner().Step(delta_t);
}
void NullSink::StepPost(duration_t delta_t)
{
}

void NullSink::StepToPre(timestamp_t timestamp)
{
  source0_.Owner().StepTo(timestamp);
}
void NullSink::StepToPost(timestamp_t timestamp)
{
}



#if GRAPH_UTILS
uint8_t NullSink::GetNumChildren()
{
  return 1;
}
GraphObjectBasePtr NullSink::GetChild(uint8_t index)
{
  return (index == 0) ? &source0_.Owner() : nullptr;
}
#endif


} // namespace synth
