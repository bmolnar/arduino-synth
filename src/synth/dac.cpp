#include "dac.h"

namespace synth {

Dac::Dac()
{
}

Dac::~Dac()
{
}

SignalSink& Dac::Input()
{
  return input_;
}

void Dac::StepToPre(timestamp_t timestamp)
{
  if (input_.Connected()) {
    input_.Source()->Owner().StepTo(timestamp);
    SetVoltage(input_.Source()->GetValue());
  }
}

void Dac::StepToPost(timestamp_t timestamp)
{
  ((void) timestamp);
}

#ifdef GRAPH_UTILS

uint8_t Dac::GetNumChildren()
{
  return (Input().Connected()) ? 1 : 0;
}

GraphObjectBasePtr Dac::GetChild(uint8_t index)
{
  return (Input().Connected() && index == 0) ? &Input().Source()->Owner() : nullptr;
}

#endif // GRAPH_UTILS

} // namespace synth
