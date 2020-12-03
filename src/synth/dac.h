#ifndef SYNTH__DAC_H_
#define SYNTH__DAC_H_

#include "types.h"
#include "graph.h"

namespace synth {

class Dac : public GraphObject<Dac>
{
public:
  Dac();
  virtual ~Dac();
  virtual void Begin() = 0;
  virtual void SetVoltage(voltage_t voltage) = 0;
  virtual void StepToPre(timestamp_t timestamp);
  virtual void StepToPost(timestamp_t timestamp);
  virtual SignalSink& Input();

#if GRAPH_UTILS
  uint8_t GetNumChildren();
  GraphObjectBasePtr GetChild(uint8_t index);
#endif

protected:
  SignalSink input_{*this};
};

} // namespace synth

#endif // SYNTH__DAC_H_
