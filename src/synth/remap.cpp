#include "remap.h"

namespace synth {

//
// Remap
//
Remap::Remap(Mapper& mapper)
 : mapper_(mapper)
{
}

Remap::Remap(Mapper& mapper, SignalSource& input)
 : mapper_(mapper), input_{*this, input}
{
}

voltage_t Remap::Value()
{
  voltage_t voltage = input_.Connected() ? input_.GetValue() : 0;
  //return RemapVoltage(params_, voltage);
  return mapper_.Map(voltage);
}

SignalSink& Remap::Input()
{
  return input_;
}

SignalSource& Remap::Output()
{
  return output_;
}

void Remap::StepToPre(timestamp_t timestamp)
{
  if (input_.Connected()) {
    input_.Source()->Owner().StepTo(timestamp);
  }
}

void Remap::StepToPost(timestamp_t timestamp)
{
  ((void) timestamp);
}

#if GRAPH_UTILS
uint8_t Remap::GetNumChildren()
{
  return input_.Connected() ? 1 : 0;
}

GraphObjectBasePtr Remap::GetChild(uint8_t index)
{
  return (input_.Connected() && index == 0) ? &input_.Source()->Owner() : nullptr;
}
#endif // GRAPH_UTILS

//
// RemapValueGetter
//
voltage_t RemapValueGetter::Get()
{
  return remap_.Value();
}

} // namespace synth
