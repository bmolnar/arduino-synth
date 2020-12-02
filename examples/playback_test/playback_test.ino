#include <synth.h>

namespace pitch = synth::pitch;



synth::Note notes[] = {
  synth::Note::Make(synth::kQuarterNote, pitch::Pitch_C2), synth::Note::Make(synth::kQuarterNote, pitch::Pitch_D2),
  synth::Note::Make(synth::kQuarterNote, pitch::Pitch_E2), synth::Note::Make(synth::kQuarterNote, pitch::Pitch_F2),
  synth::Note::Make(synth::kQuarterNote, pitch::Pitch_G2), synth::Note::Make(synth::kQuarterNote, pitch::Pitch_A2),
  synth::Note::Make(synth::kQuarterNote, pitch::Pitch_B2), synth::Note::Make(synth::kQuarterNote, pitch::Pitch_C3),
  synth::Note::Make(synth::kEighthNote, pitch::Pitch_C2), synth::Note::Make(synth::kEighthNote, pitch::Pitch_D2),
  synth::Note::Make(synth::kEighthNote, pitch::Pitch_E2), synth::Note::Make(synth::kEighthNote, pitch::Pitch_F2),
  synth::Note::Make(synth::kEighthNote, pitch::Pitch_G2), synth::Note::Make(synth::kEighthNote, pitch::Pitch_A2),
  synth::Note::Make(synth::kEighthNote, pitch::Pitch_B2), synth::Note::Make(synth::kEighthNote, pitch::Pitch_C3),
  synth::Note::End()
};


synth::Playback playback(synth::milliseconds(1000), &notes[0]);

//synth::Remap remap({synth::millivolts(-10000), synth::millivolts(10000), synth::millivolts(0), synth::millivolts(5000)});
//synth::Remap remap({synth::millivolts(0), synth::millivolts(5000), synth::millivolts(0), synth::millivolts(5000)});
synth::Remap remap({synth::millivolts(0), synth::millivolts(10000), synth::millivolts(0), synth::millivolts(5000)});

//synth::DacMcp4725 dac;
//synth::DacPrint dac(Serial, synth::milliseconds(500));
synth::DacPrintGraph dac(Serial, synth::milliseconds(500));

synth::DigitalOut dout(8);

synth::Connection conn0(playback.Output(), remap.Input());
synth::Connection conn1(remap.Output(), dac.Input());
synth::Connection conn2(playback.GateOutput(), dout.Input());

synth::Clock clock;

void setup() {
  Serial.begin(9600);
  clock.Start();
  dac.Begin();
}

void loop() {
  synth::timestamp_t timestamp = clock.Now();
  dac.StepTo(timestamp);
  dout.StepTo(timestamp);
}
