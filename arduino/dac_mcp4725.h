#ifndef SYNTH__DAC_MCP4725_H_
#define SYNTH__DAC_MCP4725_H_

#include <Wire.h>
#include <Adafruit_MCP4725.h>

#include "dac.h"

namespace synth {

class DacMcp4725 : public Dac
{
public:
  DacMcp4725();
  virtual void Begin();
  virtual void SetVoltage(voltage_t voltage);
protected:
  Adafruit_MCP4725 mcp4725_;
};

} // namespace synth

#endif // SYNTH__DAC_MCP4725_H_
