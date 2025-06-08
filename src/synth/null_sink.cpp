#include "null_sink.h"

namespace synth {

NullSink::NullSink()
  : input_{*this}
{
}

NullSink::NullSink(SignalSource& source)
  : input_{*this, source}
{
}

SignalSink& NullSink::Input()
{
  return input_;
}

void NullSink::StepToPre(timestamp_t timestamp)
{
  if (input_.Connected()) {
    input_.Source()->Owner().StepTo(timestamp);
  }
}

void NullSink::StepToPost(timestamp_t timestamp)
{
  ((void) timestamp);
}

#if GRAPH_UTILS
uint8_t NullSink::GetNumChildren()
{
  return input_.Connected() ? 1 : 0;
}

GraphObjectBasePtr NullSink::GetChild(uint8_t index)
{
  return (input_.Connected() && (index == 0)) ? &input_.Source()->Owner() : nullptr;
}
#endif // GRAPH_UTILS

} // namespace synth
