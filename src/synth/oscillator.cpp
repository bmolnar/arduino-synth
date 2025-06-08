#include "oscillator.h"

namespace synth {

//
// Oscillator
//
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

voltage_t Oscillator::Value()
{
  return static_cast<voltage_t>(static_cast<int32_t>(offset_) + (static_cast<int32_t>(amplitude_) * static_cast<int32_t>((*waveform_)(DurationToPhase(accum_, period_)))) / 32767);
}

SignalSource& Oscillator::Output()
{
  return output_;
}

void Oscillator::StepToPre(timestamp_t timestamp)
{
  accum_ = (accum_ + (timestamp - timestamp_)) % period_;
}

void Oscillator::StepToPost(timestamp_t timestamp)
{
  ((void) timestamp);
}

//
// OscillatorValueGetter
//
voltage_t OscillatorValueGetter::Get()
{
  return osc_.Value();
}

} // namespace synth
