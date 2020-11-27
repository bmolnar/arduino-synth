#include <synth.h>

namespace note = synth::notes::voltage;

synth::voltage_t slots[] = {
  note::Note_E2, note::Note_G2, note::Note_A2, note::Note_G2,
  note::Note_D3, note::Note_C3, note::Note_D3, note::Note_E3
};
synth::Sequencer seq(synth::milliseconds(1000), synth::kDutyHalf, slots, 8);
synth::DacPrint dac(Serial, synth::milliseconds(500));

synth::Timer timer;

void setup() {
  Serial.begin(9600);
  timer.Start();
}

void loop() {
  synth::duration_t delta_t = timer.ElapsedSinceLast();
  seq.Step(delta_t);
  synth::voltage_t value = seq.Value();
  dac.SetVoltage(value);
  dac.Step(delta_t);
}
