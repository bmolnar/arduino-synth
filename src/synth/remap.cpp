#include "remap.h"

namespace synth {

//
// Remap
//
Remap::Remap(const RemapParams& params)
 : params_(params)
{
}
Remap::Remap(const RemapParams& params, SignalSource& input)
 : params_(params)
{
  input_.Connect(input);
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
voltage_t Remap::Value()
{
  voltage_t voltage = input_.Connected() ? input_.GetValue() : 0;
  return static_cast<voltage_t>((static_cast<int32_t>(voltage) - static_cast<int32_t>(params_.in_min)) * (static_cast<int32_t>(params_.out_max) - static_cast<int32_t>(params_.out_min)) / (static_cast<int32_t>(params_.in_max) - static_cast<int32_t>(params_.in_min)));
}
SignalSink& Remap::Input()
{
  return input_;
}
SignalSource& Remap::Output()
{
  return output_;
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
  return remap_->Value();
}

} // namespace synth
