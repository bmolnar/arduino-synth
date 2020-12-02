#include <synth.h>

synth::Oscillator osc0(synth::WaveformSine, synth::milliseconds(1000), synth::millivolts(5000), synth::millivolts(5000));


//synth::Remap remap({synth::millivolts(-10000), synth::millivolts(10000), synth::millivolts(0), synth::millivolts(5000)});
//synth::Remap remap({synth::millivolts(0), synth::millivolts(5000), synth::millivolts(0), synth::millivolts(5000)});
synth::Remap remap({synth::millivolts(0), synth::millivolts(10000), synth::millivolts(0), synth::millivolts(5000)});


synth::DacMcp4725 dac;
//synth::DacPrintGraph dac(Serial, synth::milliseconds(50));


synth::Connection conn0(osc0.Output(), remap.Input());
synth::Connection conn1(remap.Output(), dac.Input());
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
    //PrintGraph(Serial, &dac2);
  }
  synth::timestamp_t timestamp = clock.Now();
  dac.StepTo(timestamp);
}
