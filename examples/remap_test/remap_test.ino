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


synth::Timer timer;

synth::timestamp_t g_timestamp = 0;
unsigned long g_loopcnt = 0;

void setup() {
  Serial.begin(9600);
  timer.Start();
  dac.Begin();
}

void loop() {
  synth::duration_t delta_t = timer.ElapsedSinceLast();
  g_timestamp += delta_t;

  dac.StepTo(g_timestamp);
  if ((g_loopcnt % 1024) == 0) {
    //PrintGraph(Serial, &dac2);
  }

}
