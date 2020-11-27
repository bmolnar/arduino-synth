#include <synth.h>

synth::Oscillator osc0(synth::WaveformSine, synth::milliseconds(1000), synth::millivolts(1000), synth::millivolts(1000));
synth::Oscillator osc1(synth::WaveformSine, synth::milliseconds(1000), synth::millivolts(500), synth::millivolts(500));
synth::Oscillator osc2(synth::WaveformSine, synth::milliseconds(1000), synth::millivolts(100), synth::millivolts(100));
synth::Oscillator osc3(synth::WaveformSine, synth::milliseconds(100), synth::millivolts(50), synth::millivolts(50));

synth::OscillatorPtr osc_list[] = {&osc0, &osc1, &osc2, &osc3};

synth::DacPrint dac0(Serial, synth::milliseconds(1000));
synth::DacMcp4725 dac1;
synth::DacPrintGraph dac2(Serial, synth::milliseconds(50));


synth::Timer timer;

synth::timestamp_t g_timestamp = 0;
unsigned long g_loopcnt = 0;

void setup() {
  Serial.begin(115200);
  timer.Start();

  dac2.Input().Connect(osc0.Output());
}

void loop() {
  synth::duration_t delta_t = timer.ElapsedSinceLast();
  g_timestamp += delta_t;

  dac2.StepTo(g_timestamp);

  if ((g_loopcnt % 1024) == 0) {
    //PrintGraph(Serial, &dac2);
  }

}
