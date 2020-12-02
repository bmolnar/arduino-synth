#ifndef SYNTH__DAC_PRINT_GRAPH_H_
#define SYNTH__DAC_PRINT_GRAPH_H_

#include <Arduino.h>

#include "dac.h"

namespace synth {

class DacPrintGraph : public Dac
{
public:
  DacPrintGraph(Print& print, duration_t sample_period=milliseconds(100));
  DacPrintGraph(Print& print, SignalSource& source, duration_t sample_period=milliseconds(100));
  virtual void Begin();

  virtual void StepPre(duration_t delta_t);
  virtual void StepPost(duration_t delta_t);

  virtual void StepToPre(timestamp_t timestamp);
  virtual void StepToPost(timestamp_t timestamp);

  virtual void SetVoltage(voltage_t voltage);
  void PrintHoriz(voltage_t value);
  void PrintSpaces(uint8_t count);
  void PrintScaleLine();

protected:
  Print& print_;
  duration_t sample_period_;
  duration_t sample_accum_{0};
  voltage_t last_value_;
  unsigned long printcnt_{0};
};

} // namespace synth

#endif // SYNTH__DAC_PRINT_GRAPH_H_
