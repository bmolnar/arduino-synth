#include <synth.h>

synth::Oscillator osc0(synth::WaveformSine, synth::milliseconds(1000), synth::millivolts(5000), synth::millivolts(0));

synth::MapperLinear mapper({synth::millivolts(-5000), synth::millivolts(5000), synth::millivolts(0), synth::millivolts(5000)});
synth::Remap remap(mapper, osc0.Output());

//synth::DacMcp4725 dac(remap.Output());
synth::DacPrintGraph dac(Serial, remap.Output(), synth::milliseconds(100));

synth::Clock clock;

unsigned long g_loopcnt = 0;

void setup() {
  Serial.begin(9600);
  clock.Start();
  dac.Begin();
}

void loop() {
  if (g_loopcnt++ == 0) {
    //PrintGraph(Serial, &dac2);
  }
  synth::timestamp_t timestamp = clock.Now();
  dac.StepTo(timestamp);
}
