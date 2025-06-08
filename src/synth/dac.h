#ifndef SYNTH__DAC_H_
#define SYNTH__DAC_H_

#include "types.h"
#include "graph.h"

namespace synth {

/**
 * Dac
 *
 * Abstract base class for implementations of digital-to-analog converters
 *
 * Derived classes must implement the `SetVoltage` method.
 */
class Dac : public GraphObject<Dac>
{
public:
  Dac();
  virtual ~Dac();

  /**
   * Initiates runtime operation
   *
   * To be called by user before operation begins
   *
   * (his is an abstract method and must be defined by derived classes
   */
  virtual void Begin() = 0;

  /**
   * Sets the output voltage
   *
   * This is an abstract method and must be defined by derived classes
   *
   * @param voltage Output value in Volts
   */
  virtual void SetVoltage(voltage_t voltage) = 0;

  /**
   * Gets input as a `SignalSink` object
   *
   * Can be overwritten by derived classes
   *
   * @return A reference to the input `SignalSink` object
   */
  virtual SignalSink& Input();

  /**
   * Called by run graph just before `StepTo`
   *
   * Can be overwritten by derived classes
   *
   * @param timestamp The time stamp provided in the `StepTo` call
   */
  virtual void StepToPre(timestamp_t timestamp);

  /**
   * Called by run graph just after `StepTo`
   *
   * Can be overwritten by derived classes
   *
   * @param timestamp The time stamp provided in the `StepTo` call
   */
  virtual void StepToPost(timestamp_t timestamp);

#if GRAPH_UTILS
  uint8_t GetNumChildren();
  GraphObjectBasePtr GetChild(uint8_t index);
#endif // GRAPH_UTILS

protected:
  SignalSink input_{*this};
};

} // namespace synth

#endif // SYNTH__DAC_H_
