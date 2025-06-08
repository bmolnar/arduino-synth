#ifndef SYNTH__DAC_PRINT_GRAPH_H_
#define SYNTH__DAC_PRINT_GRAPH_H_

#include <Arduino.h>

#include "dac.h"

namespace synth {

/**
 * DacPrintGraph
 *
 * Functions as a digital-to-analog converter, but whose output is printed
 * in graphical format.
 */
class DacPrintGraph : public Dac
{
public:
  static constexpr uint8_t kLeftWidth = 8;
  static constexpr uint8_t kMiddleWidth = 81;
  static constexpr uint8_t kRightWidth = 8;

  /**
   * Initializes object with Print object and flush duration
   *
   * @param print A Print object where the output is sent to
   * @param flush_period How often the Print object is flushed
   */
  DacPrintGraph(Print& print, duration_t sample_period=milliseconds(100));

  /**
   * Initializes object with Print object, signal source, and flush duration
   *
   * @param print A Print object where the output is sent to
   * @param source A SignalSource object that supplies the signal to this
                   component
   * @param flush_period How often the Print object is flushed
   */
  DacPrintGraph(Print& print, SignalSource& source, duration_t sample_period=milliseconds(100));

  /**
   * Initiates runtime operation
   *
   * To be called by user before operation begins
   */
  virtual void Begin();

  /**
   * Sets output voltage of DAC
   *
   * This value is printed (graphically) to the output
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

  void PrintSpaces(uint8_t count);
  void PrintScaleLine();
  void PrintHoriz(voltage_t value, timestamp_t timestamp);

protected:
  Print& print_;
  duration_t sample_period_;
  duration_t sample_accum_{0};
  voltage_t last_value_;
  timestamp_t last_timestamp_{0};
  unsigned long printcnt_{0};
};

} // namespace synth

#endif // SYNTH__DAC_PRINT_GRAPH_H_
