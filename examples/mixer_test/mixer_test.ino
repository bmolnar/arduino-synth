#include <synth.h>

synth::Oscillator osc0(synth::WaveformSine, synth::milliseconds(6000), synth::millivolts(2000), synth::millivolts(2000));
synth::Oscillator osc1(synth::WaveformSine, synth::milliseconds(3000), synth::millivolts(1000), synth::millivolts(1000));
synth::Oscillator osc2(synth::WaveformSine, synth::milliseconds(2000), synth::millivolts(500), synth::millivolts(500));
synth::Oscillator osc3(synth::WaveformSine, synth::milliseconds(1000), synth::millivolts(100), synth::millivolts(100));
synth::Mixer mixer0(osc0.Output(), osc1.Output(), osc2.Output(), osc3.Output());
synth::Mixer mixer1(osc0.Output(), osc1.Output(), osc2.Output(), osc3.Output());
synth::Mixer mixer2(mixer0.Output(), mixer1.Output());
synth::DacPrint dac(Serial, mixer2.Output(), synth::milliseconds(1000));
synth::NullSink sink(mixer2.Output());

synth::Timer timer;

unsigned long g_loopcnt = 0;
synth::timestamp_t g_timestamp = 0;

void setup() {
  Serial.begin(9600);
  timer.Start();
}

void loop() {
  synth::duration_t delta_t = timer.ElapsedSinceLast();
  g_timestamp += delta_t;
  
  //dac.StepTo(g_timestamp);
  sink.StepTo(g_timestamp);
  if ((g_loopcnt % 1024) == 0) {
    PrintGraph(Serial, &sink);
  }
}
