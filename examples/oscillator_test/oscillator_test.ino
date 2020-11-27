#include <synth.h>

synth::Oscillator osc(synth::WaveformSine, synth::milliseconds(1000), synth::millivolts(1000), synth::millivolts(2000));
synth::DacPrint dac(Serial, synth::milliseconds(2000));

synth::Timer timer;

void setup() {
  Serial.begin(9600);
  timer.Start();
}

void loop() {
  synth::duration_t delta_t = timer.ElapsedSinceLast();
  osc.Step(delta_t);
  synth::voltage_t value = osc.Value();
  dac.SetVoltage(value);
  dac.Step(delta_t);
}
