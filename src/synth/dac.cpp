#include "dac.h"

namespace synth {

Dac::Dac()
{
}
Dac::~Dac()
{
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
