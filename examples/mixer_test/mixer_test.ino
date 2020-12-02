#include <synth.h>

synth::Oscillator osc0(synth::WaveformSine, synth::milliseconds(4000), synth::millivolts(4000), synth::millivolts(0));
synth::Oscillator osc1(synth::WaveformSine, synth::milliseconds(2000), synth::millivolts(2000), synth::millivolts(0));
synth::Oscillator osc2(synth::WaveformSine, synth::milliseconds(1000), synth::millivolts(1000), synth::millivolts(0));
synth::Oscillator osc3(synth::WaveformSine, synth::milliseconds(500), synth::millivolts(500), synth::millivolts(0));

synth::Mixer4 mixer0(osc0.Output(), synth::kGainUnity, osc1.Output(), 0, osc2.Output(), 0, osc3.Output(), 0);
synth::Mixer4 mixer1(osc0.Output(), 0, osc1.Output(), synth::kGainUnity, osc2.Output(), 0, osc3.Output(), 0);
synth::Mixer4 mixer2(osc0.Output(), 0, osc1.Output(), 0, osc2.Output(), synth::kGainUnity, osc3.Output(), 0);
synth::Mixer4 mixer3(osc0.Output(), 0, osc1.Output(), 0, osc2.Output(), 0, osc3.Output(), synth::kGainUnity);


// [1,  1,  1,  1]
// [1,  1, -1, -1]
// [1, -1,  1, -1]
// [1, -1, -1,  1]
synth::Mixer4 mixer_all(mixer0.Output(), synth::kGainUnity, mixer1.Output(), synth::kGainUnity, mixer2.Output(), synth::kGainUnity, mixer3.Output(), synth::kGainUnity);
synth::Mixer4 mixer_lower(mixer0.Output(), synth::kGainUnity, mixer1.Output(), synth::kGainUnity, mixer2.Output(), -synth::kGainUnity, mixer3.Output(), -synth::kGainUnity);
synth::Mixer4 mixer_even(mixer0.Output(), synth::kGainUnity, mixer1.Output(), -synth::kGainUnity, mixer2.Output(), synth::kGainUnity, mixer3.Output(), -synth::kGainUnity);
synth::Mixer4 mixer_outer(mixer0.Output(), synth::kGainUnity, mixer1.Output(), -synth::kGainUnity, mixer2.Output(), -synth::kGainUnity, mixer3.Output(), synth::kGainUnity);

#define GAINS0 synth::kGainUnity, synth::kGainUnity, synth::kGainUnity, synth::kGainUnity
#define GAINS1 synth::kGainUnity, synth::kGainUnity, -synth::kGainUnity, -synth::kGainUnity
#define GAINS2 synth::kGainUnity, -synth::kGainUnity, synth::kGainUnity, -synth::kGainUnity
#define GAINS3 synth::kGainUnity, -synth::kGainUnity, -synth::kGainUnity, synth::kGainUnity

synth::Mixer4 mixer_top(mixer_all.Output(), mixer_lower.Output(), mixer_even.Output(), mixer_outer.Output(),
                        GAINS1, (synth::kGainUnity/4));


//synth::DacPrint dac(Serial, synth::milliseconds(1000));
synth::DacPrintGraph dac(Serial, synth::milliseconds(500));
//synth::DacMcp4725 dac;

synth::Connection conn0(mixer_top.Output(), dac.Input());
//synth::Connection conn0(mixer0.Output(), dac.Input());
//synth::Connection conn0(osc0.Output(), dac.Input());


//synth::NullSink sink;
//synth::Connection conn1(mixer_top.Output(), sink.Input());

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
  //sink.StepTo(timestamp);
}
