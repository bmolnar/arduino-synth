#include "oscillator.h"

namespace synth {

Oscillator::Oscillator(NormalizedWaveform waveform, duration_t period, voltage_t amplitude, voltage_t offset)
    : waveform_(waveform), period_(period), amplitude_(amplitude), offset_(offset)
{
}
void Oscillator::SetWaveform(NormalizedWaveform waveform)
{
  waveform_ = waveform;
}
void Oscillator::SetPeriod(duration_t period)
{
  period_ = period;
}
void Oscillator::SetAmplitude(voltage_t amplitude)
{
  amplitude_ = amplitude;
}
void Oscillator::SetOffset(voltage_t offset)
{
  offset_ = offset;
}

void Oscillator::StepPre(duration_t delta_t)
{
  ((void) delta_t);
}
void Oscillator::StepPost(duration_t delta_t)
{
  phase_ += static_cast<uint16_t>(delta_t * 65536 / period_);
}


void Oscillator::StepToPre(timestamp_t timestamp)
{
  phase_ += static_cast<uint16_t>((timestamp - timestamp_) * 65536 / period_);
}
void Oscillator::StepToPost(timestamp_t timestamp)
{
  ((void) timestamp);
}

voltage_t Oscillator::Value()
{
  return static_cast<voltage_t>(static_cast<int32_t>(offset_) + (static_cast<int32_t>(amplitude_) * static_cast<int32_t>((*waveform_)(phase_))) / 32767);
}
SignalSource& Oscillator::Output()
{
  return output_;
}

voltage_t OscillatorValueGetter::Get()
{
  return osc_->Value();
}

} // namespace synth
