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


/**
 * DacPrint
 *
 * Functions as a digital-to-analog converter, but whose output is printed
 * as numerical values.
 */
class DacPrint : public Dac
{
public:
  /**
   * Initializes object with Print object and flush duration
   *
   * @param print A Print object where the output is sent to
   * @param flush_period How often the Print object is flushed
   */
  DacPrint(Print& print, duration_t flush_period=milliseconds(1000));

  /**
   * Initializes object with Print object, signal source, and flush duration
   *
   * @param print A Print object where the output is sent to
   * @param source A SignalSource object that supplies the signal to this
                   component
   * @param flush_period How often the Print object is flushed
   */
  DacPrint(Print& print, SignalSource& source, duration_t flush_period=milliseconds(1000));

  virtual void Begin();

  /**
   * Sets output voltage of DAC
   *
   * This value is printed (numerically) to the output
   *
   * @param voltage Output voltage to be printed
   */
  virtual void SetVoltage(voltage_t voltage);

  /**
   * Called just before StepTo by run graph
   *
   * @param timestamp The time stamp provided in the StepTo call
   */
  virtual void StepToPre(timestamp_t timestamp);

  /**
   * Called just after StepTo by run graph
   *
   * @param timestamp The time stamp provided in the StepTo call
   */
  virtual void StepToPost(timestamp_t timestamp);

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
