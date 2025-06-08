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


/**
 * Oscillator
 *
 * Provides periodic signal with a given waveform, frequency, amplitude and
 * offset
 */
class Oscillator : public GraphObject<Oscillator>
{
public:

  /**
   * Initializes object with given waveform, period, amplitude and offset
   *
   * @param waveform A NormalizedWaveform value representing the periodic
   *                 waveform of the output signal
   * @param period The period of the output signal, in microseconds
   * @param amplitude The amplitude of the output signal, in mV
   * @param offset The DC offset of the output signal, in mV
   */
  Oscillator(NormalizedWaveform waveform, duration_t period, voltage_t amplitude=millivolts(1000), voltage_t offset=millivolts(0));

  /**
   * Sets the waveform of the output signal
   *
   * @param waveform A NormalizedWaveform value representing the periodic
   *                 waveform of the output signal
   */
  void SetWaveform(NormalizedWaveform waveform);

  /**
   * Sets the period of the output signal
   *
   * @param period The period of the output signal, in microseconds
   */
  void SetPeriod(duration_t period);

  /**
   * Sets the amplitude of the output signal
   *
   * @param amplitude The amplitude of the output signal, in mV
   */
  void SetAmplitude(voltage_t amplitude);

  /**
   * Sets the DC offset of the output signal
   *
   * @param offset The DC offset of the output signal, in mV
   */
  void SetOffset(voltage_t offset);

  /**
   * Gets the current value of the output signal
   *
   * @return The current value of the output signal, in mV
   */
  voltage_t Value();

  /**
   * Gets a reference to the output SignalSource for the oscillator
   *
   * @return A reference to the SignalSource of the oscillator output
   */
  SignalSource& Output();

  /**
   * Called by run graph just before StepTo
   *
   * @param timestamp The time stamp provided in the StepTo call
   */
  void StepToPre(timestamp_t timestamp);

  /**
   * Called by run graph just after StepTo
   *
   * @param timestamp The time stamp provided in the StepTo call
   */
  void StepToPost(timestamp_t timestamp);

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
