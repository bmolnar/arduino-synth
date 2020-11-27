#include "dac.h"

namespace synth {


void Dac::StepPre(duration_t delta_t)
{
  if (input_.Connected()) {
    input_.Source()->Owner().Step(delta_t);
    voltage_t value = input_.Source()->GetValue();
    SetVoltage(value);
  }
}
void Dac::StepPost(duration_t delta_t)
{
  ((void) delta_t);
}


void Dac::StepToPre(timestamp_t timestamp)
{
  if (input_.Connected()) {
    input_.Source()->Owner().StepTo(timestamp);
    voltage_t value = input_.Source()->GetValue();
    SetVoltage(value);
  }
}
void Dac::StepToPost(timestamp_t timestamp)
{
  ((void) timestamp);
}


SignalSink& Dac::Input()
{
  return input_;
}

#ifdef GRAPH_UTILS
uint8_t Dac::GetNumChildren()
{
  return (input_.Connected()) ? 1 : 0;
}
GraphObjectBasePtr Dac::GetChild(uint8_t index)
{
  return (input_.Connected() && index == 0) ? &input_.Source()->Owner() : nullptr;
}
#endif


} // namespace synth
