#include "dac_remap.h"

namespace synth {

DacRemap::DacRemap(Dac& dac, Mapper& mapper)
  : dac_(dac), mapper_(mapper), remap_(mapper), conn_(remap_.Output(), dac_.Input())
{
}
DacRemap::DacRemap(Dac& dac, Mapper& mapper, SignalSource& source)
  : dac_(dac), mapper_(mapper), remap_(mapper, source), conn_(remap_.Output(), dac_.Input())
{
}

void DacRemap::Begin()
{
  dac_.Begin();
}
void DacRemap::StepToPre(timestamp_t timestamp)
{
  dac_.StepToPre(timestamp);
}
void DacRemap::StepToPost(timestamp_t timestamp)
{
  dac_.StepToPost(timestamp);
}
void DacRemap::SetVoltage(voltage_t voltage)
{
  dac_.SetVoltage(mapper_.Map(voltage));
}
SignalSink& DacRemap::Input()
{
  return remap_.Input();
}


#if GRAPH_UTILS
uint8_t DacRemap::GetNumChildren()
{
  return (Input().Connected()) ? 1 : 0;
}
GraphObjectBasePtr DacRemap::GetChild(uint8_t index)
{
  return (Input().Connected() && index == 0) ? &Input().Source()->Owner() : nullptr;
}
#endif


} // namespace synth
