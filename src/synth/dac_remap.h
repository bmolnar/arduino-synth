#ifndef SYNTH__DAC_REMAP_H_
#define SYNTH__DAC_REMAP_H_

#include "dac.h"
#include "remap.h"
#include "graph.h"

namespace synth {

/**
 * DacRemap
 *
 * A wrapper for a Dac object that uses a Mapper to remap values before given
 * to the Dac
 */
class DacRemap : public Dac
{
public:

  /**
   * Initializes object with a given Dac instance and a Mapper
   *
   * @param dac A reference to the Dac object to use for output
   * @param mapper A reference to the mapper to use for remapping values
   */
  DacRemap(Dac& dac, Mapper& mapper);

  /**
   * Initializes object with a given Dac instance and a Mapper and then
   * connects to a given SignalSource
   *
   * @param dac A reference to the Dac object to use for output
   * @param mapper A reference to the Mapper to use for remapping values
   * @param source A reference to a SignalSource that will be connected
   */
  DacRemap(Dac& dac, Mapper& mapper, SignalSource& source);

  /**
   * Initiates runtime operation
   *
   * To be called by user before operation begins
   */
  virtual void Begin();

  /**
   * Sets output voltage of DAC
   *
   * Actual output voltage will be remapped
   *
   * @param voltage Output voltage
   */
  virtual void SetVoltage(voltage_t voltage);

  /**
   * Gets a reference to the SignalSink for the input
   *
   * @return A reference to the SignalSink of the input
   */
  virtual SignalSink& Input();

  /**
   * Called by run graph just before StepTo
   *
   * @param timestamp The time stamp provided in the StepTo call
   */
  virtual void StepToPre(timestamp_t timestamp);

  /**
   * Called by run graph just after StepTo
   *
   * @param timestamp The time stamp provided in the StepTo call
   */
  virtual void StepToPost(timestamp_t timestamp);

#if GRAPH_UTILS
  uint8_t GetNumChildren();
  GraphObjectBasePtr GetChild(uint8_t index);
#endif // GRAPH_UTILS

protected:
  Dac& dac_;
  Mapper& mapper_;
  Remap remap_;
  Connection conn_;
};

} // namespace synth

#endif // SYNTH__DAC_REMAP_H_
