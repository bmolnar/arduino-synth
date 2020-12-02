#include "digital_out.h"

#include <Arduino.h>

namespace synth {

DigitalOut::DigitalOut(int pin)
  : pin_(pin)
{
}

DigitalOut::~DigitalOut()
{
}

void DigitalOut::Begin()
{
  pinMode(pin_, OUTPUT);
}

void DigitalOut::SetVoltage(voltage_t voltage)
{
  digitalWrite(pin_, (voltage >= kHighThreshold) ? HIGH : LOW);
}

void DigitalOut::StepPre(duration_t delta_t)
{
  if (input_.Connected()) {
    input_.Source()->Owner().Step(delta_t);
    SetVoltage(input_.Source()->GetValue());
  }
}
void DigitalOut::StepPost(duration_t delta_t)
{
  ((void) delta_t);
}

void DigitalOut::StepToPre(timestamp_t timestamp)
{
  if (input_.Connected()) {
    input_.Source()->Owner().StepTo(timestamp);
    SetVoltage(input_.Source()->GetValue());
  }
}
void DigitalOut::StepToPost(timestamp_t timestamp)
{
  ((void) timestamp);
}

SignalSink& DigitalOut::Input()
{
  return input_;
}

} // namespace synth
