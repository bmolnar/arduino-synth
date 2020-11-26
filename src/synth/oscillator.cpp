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
void Oscillator::Step(duration_t delta_t)
{
  phase_ += static_cast<uint16_t>(delta_t * 65536 / period_);
}
voltage_t Oscillator::Value()
{
  return static_cast<voltage_t>(static_cast<int32_t>(offset_) + (static_cast<int32_t>(amplitude_) * static_cast<int32_t>((*waveform_)(phase_))) / 32767);
}
SignalSourcePtr Oscillator::Output()
{
  return &output_;
}


void OscillatorSignalSource::Step(duration_t delta_t)
{
  osc_->Step(delta_t);
}
voltage_t OscillatorSignalSource::Value()
{
  return osc_->Value();
}

} // namespace synth
