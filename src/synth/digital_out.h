#ifndef SYNTH__DIGITAL_OUT_H_
#define SYNTH__DIGITAL_OUT_H_

#include "types.h"
#include "graph.h"

namespace synth {

class DigitalOut : public GraphObject<DigitalOut>
{
public:
  static constexpr voltage_t kHighThreshold = millivolts(3300);

  DigitalOut(int pin);
  DigitalOut(int pin, SignalSource& source);

  ~DigitalOut();
  void Begin();
  void SetVoltage(voltage_t voltage);
  void StepToPre(timestamp_t timestamp);
  void StepToPost(timestamp_t timestamp);
  SignalSink& Input();

protected:
  int pin_;
  SignalSink input_{*this};
};

} // namespace synth

#endif // SYNTH__DAC_MCP4725_H_
