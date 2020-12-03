#ifndef SYNTH__DAC_REMAP_H_
#define SYNTH__DAC_REMAP_H_

#include "dac.h"
#include "remap.h"
#include "graph.h"

namespace synth {

class DacRemap : public Dac
{
public:
  DacRemap(Dac& dac, Mapper& mapper);
  DacRemap(Dac& dac, Mapper& mapper, SignalSource& source);
  virtual void Begin();
  virtual void StepToPre(timestamp_t timestamp);
  virtual void StepToPost(timestamp_t timestamp);
  virtual void SetVoltage(voltage_t voltage);
  virtual SignalSink& Input();

#if GRAPH_UTILS
  uint8_t GetNumChildren();
  GraphObjectBasePtr GetChild(uint8_t index);
#endif

protected:
  Dac& dac_;
  Mapper& mapper_;
  Remap remap_;
  Connection conn_;
};

} // namespace synth

#endif // SYNTH__DAC_REMAP_H_
