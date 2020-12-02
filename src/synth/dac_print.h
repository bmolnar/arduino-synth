#ifndef SYNTH__DAC_PRINT_H_
#define SYNTH__DAC_PRINT_H_

#include <Arduino.h>

#include "dac.h"

namespace synth {

struct DacPrintStats
{
  voltage_t min_value{kVoltageMax};
  voltage_t max_value{kVoltageMin};
  voltage_t last_value{0};
  int32_t accum_sum{0};
  uint32_t accum_sum_sq{0};
  duration_t accum_time{0};
  uint32_t updates{0};
};

class DacPrint : public Dac
{
public:
  DacPrint(Print& print, duration_t flush_period=milliseconds(1000));
  DacPrint(Print& print, SignalSource& source, duration_t flush_period=milliseconds(1000));
  virtual void Begin();
  virtual void StepToPre(timestamp_t timestamp);
  virtual void StepToPost(timestamp_t timestamp);
  virtual void SetVoltage(voltage_t voltage);

protected:
  void PrintStats(const DacPrintStats& stats);
  void ResetStats(DacPrintStats& stats);

  Print& print_;
  duration_t flush_period_;
  duration_t flush_accum_{0};
  DacPrintStats stats_;
};

} // namespace synth

#endif // SYNTH__DAC_PRINT_H_
