#ifndef SYNTH__DAC_MCP4725_H_
#define SYNTH__DAC_MCP4725_H_

#include <Wire.h>
#include <Adafruit_MCP4725.h>

#include "dac.h"

namespace synth {

/**
 * DacMcp4725
 *
 * A digital-to-analog converter that uses the MCP4725
 */
class DacMcp4725 : public Dac
{
public:
  /**
   * Initializes object
   */
  DacMcp4725();

  /**
   * Initiates runtime operation
   *
   * To be called by user before operation begins
   */
  virtual void Begin();

  /**
   * Sets the output voltage of the MCP4725 DAC
   *
   * @param voltage Output value, in mV
   */
  virtual void SetVoltage(voltage_t voltage);

protected:
  Adafruit_MCP4725 mcp4725_;
};

} // namespace synth

#endif // SYNTH__DAC_MCP4725_H_
