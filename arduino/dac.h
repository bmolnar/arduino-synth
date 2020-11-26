#ifndef SYNTH__DAC_H_
#define SYNTH__DAC_H_

#include "types.h"

namespace synth {

class Dac
{
public:
  virtual ~Dac(){};
  virtual void Begin() = 0;
  virtual void SetVoltage(voltage_t voltage) = 0;
};

} // namespace synth

#endif // SYNTH__DAC_H_
