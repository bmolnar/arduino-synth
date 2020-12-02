#ifndef SYNTH__OSCILLATOR_H_
#define SYNTH__OSCILLATOR_H_

#include "types.h"
#include "graph.h"

namespace synth {

class Oscillator;
typedef Oscillator* OscillatorPtr;


class OscillatorValueGetter : public SignalGetter
{
public:
  OscillatorValueGetter(Oscillator& osc) : osc_(osc) {}
  virtual voltage_t Get();
protected:
  Oscillator& osc_;
};

class Oscillator : public GraphObject<Oscillator>
{
public:
  Oscillator(NormalizedWaveform waveform, duration_t period, voltage_t amplitude=millivolts(1000), voltage_t offset=millivolts(0));
  void SetWaveform(NormalizedWaveform waveform);
  void SetPeriod(duration_t period);
  void SetAmplitude(voltage_t amplitude);
  void SetOffset(voltage_t offset);

  void StepToPre(timestamp_t timestamp);
  void StepToPost(timestamp_t timestamp);
  voltage_t Value();
  SignalSource& Output();

protected:
  NormalizedWaveform waveform_;
  duration_t period_;
  voltage_t amplitude_;
  voltage_t offset_;
  duration_t accum_{0};

  OscillatorValueGetter getter_{*this};
  SignalSource output_{*this, &getter_};
};

} // namespace synth

#endif // SYNTH__OSCILLATOR_H_
