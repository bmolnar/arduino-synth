#include <synth.h>

synth::Oscillator osc0(synth::WaveformSine, synth::milliseconds(1000), synth::millivolts(5000), synth::millivolts(0));


//synth::DacMcp4725 dac_inner;
synth::DacPrintGraph dac_inner(Serial, synth::milliseconds(50));

synth::MapperLinear mapper({synth::millivolts(-5000), synth::millivolts(5000), synth::millivolts(5000), synth::millivolts(0)});
synth::DacRemap dac(dac_inner, mapper, osc0.Output());


//synth::Connection conn0(osc0.Output(), dac.Input());
//synth::Connection conn1(remap.Output(), dac.Input());
//synth::Connection conn(osc0.Output(), dac.Input());


synth::Clock clock;

unsigned long g_loopcnt = 0;

void setup() {
  Serial.begin(9600);
  clock.Start();
  dac.Begin();
}

void loop() {
  if (g_loopcnt++ == 0) {
    PrintGraph(Serial, &dac);
  }
  synth::timestamp_t timestamp = clock.Now();
  dac.StepTo(timestamp);
}
