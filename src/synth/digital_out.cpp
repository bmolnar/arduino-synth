#include "digital_out.h"

#include <Arduino.h>

namespace synth {

//
// DigitalOut
//
DigitalOut::DigitalOut(int pin)
  : pin_(pin)
{
}

DigitalOut::DigitalOut(int pin, SignalSource& source)
  : pin_(pin), input_{*this, source}
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

SignalSink& DigitalOut::Input()
{
  return input_;
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

} // namespace synth
