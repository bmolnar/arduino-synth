#ifndef SYNTH__DIGITAL_OUT_H_
#define SYNTH__DIGITAL_OUT_H_

#include "types.h"
#include "graph.h"

namespace synth {


/**
 * DigitalOut
 *
 * Wraps control of a digital output pin on the Arduino board
 */
class DigitalOut : public GraphObject<DigitalOut>
{
public:
  static constexpr voltage_t kHighThreshold = millivolts(3300);

  /**
   * Initializes digital-out object tied to given board pin
   *
   * @param pin Pin number to be controlled by this object
   */
  DigitalOut(int pin);

  /**
   * Initializes digital out object tied to given board pin
   * and connects a given SignalSource object
   *
   * @param pin Pin number to be controlled by this object
   * @param source The SignalSource object that provides input to this
   **              component
   */
  DigitalOut(int pin, SignalSource& source);

  /**
   * Deconstructs object
   */
  ~DigitalOut();

  /**
   * Initiates runtime operation
   */
  void Begin();

  /**
   * Sets output voltage of digital-out pin
   *
   * @param voltage Output voltage of pin
   */
  void SetVoltage(voltage_t voltage);

  /**
   * Gets input as a SignalSink object
   *
   * @return A reference to the input SignalSink object
   */
  SignalSink& Input();

  /**
   * Called by run graph just before StepTo
   *
   * @param timestamp The time stamp provided in the StepTo call
   */
  void StepToPre(timestamp_t timestamp);

  /**
   * Called by run graph just after StepTo
   *
   * @param timestamp The time stamp provided in the StepTo call
   */
  void StepToPost(timestamp_t timestamp);

protected:
  int pin_;
  SignalSink input_{*this};
};

} // namespace synth

#endif // SYNTH__DAC_MCP4725_H_
