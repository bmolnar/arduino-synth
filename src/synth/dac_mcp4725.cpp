#include "dac_mcp4725.h"

namespace synth {

DacMcp4725::DacMcp4725()
{
}

void DacMcp4725::Begin()
{
  mcp4725_.begin(0x60);
}

void DacMcp4725::SetVoltage(voltage_t voltage)
{
  int32_t value = static_cast<int32_t>(voltage) * 4096 / 5000;
  if (value < 0) {
    value = 0;
  } else if (value > 4095) {
    value = 4095;
  }
  mcp4725_.setVoltage(static_cast<uint16_t>(value), false);
}

} // namespace synth
