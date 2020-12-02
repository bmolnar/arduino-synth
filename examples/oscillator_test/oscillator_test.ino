#include <synth.h>

//synth::Oscillator osc(synth::WaveformSine, synth::milliseconds(1000), synth::millivolts(1000), synth::millivolts(1000));
//synth::Oscillator osc(synth::WaveformSine, synth::milliseconds(1000), synth::millivolts(500), synth::millivolts(500));
//synth::Oscillator osc(synth::WaveformSine, synth::milliseconds(1000), synth::millivolts(100), synth::millivolts(100));
synth::Oscillator osc(synth::WaveformSine, synth::milliseconds(1000), synth::millivolts(4000), synth::millivolts(0));



//synth::DacPrint dac(Serial, synth::milliseconds(1000));
//synth::DacMcp4725 dac;
synth::DacPrintGraph dac(Serial, synth::milliseconds(50));

synth::Connection conn(osc.Output(), dac.Input());



synth::NormalizedWaveform waveforms[] = {synth::WaveformSine, synth::WaveformTriangle, synth::WaveformSawtooth, synth::WaveformSquare, synth::WaveformZero};
uint8_t g_waveform_select = 0;

synth::Clock clock;


void AdvanceWaveform()
{
  g_waveform_select = (g_waveform_select + 1) % 5;
  osc.SetWaveform(waveforms[g_waveform_select]);
}

synth::Timer timer(synth::milliseconds(4000), &AdvanceWaveform);

void setup() {
  Serial.begin(9600);
  clock.Start();
  timer.Start();
  dac.Begin();
}

void loop() {
  synth::timestamp_t timestamp = clock.Now();
  timer.StepTo(timestamp);
  dac.StepTo(timestamp);
}
