#include <synth.h>

namespace pitch = synth::pitch;



#define NOTE(_d, _p) synth::Note::Normal(synth::k ## _d ## Note, synth::pitch::  _p)

synth::Note notes[] = {
  NOTE(Quarter, Pitch_A2), NOTE(Quarter, Pitch_A2), NOTE(Quarter, Pitch_A2), NOTE(DottedEighth, Pitch_F2), NOTE(Sixteenth, Pitch_C3),
  NOTE(Quarter, Pitch_A2), NOTE(DottedEighth, Pitch_F2), NOTE(Sixteenth, Pitch_C3), NOTE(Half, Pitch_A2),
  NOTE(Quarter, Pitch_E3), NOTE(Quarter, Pitch_E3), NOTE(Quarter, Pitch_E3), NOTE(DottedEighth, Pitch_F3), NOTE(Sixteenth, Pitch_C3),
  NOTE(Quarter, Pitch_Ab2), NOTE(DottedEighth, Pitch_F2), NOTE(Sixteenth, Pitch_C3), NOTE(Half, Pitch_A2),
  NOTE(Quarter, Pitch_A3), NOTE(Eighth, Pitch_A2), NOTE(Eighth, Pitch_A2), NOTE(Quarter, Pitch_A3), NOTE(Eighth, Pitch_Ab3), NOTE(Eighth, Pitch_G3),
  NOTE(Sixteenth, Pitch_Gb3), NOTE(Sixteenth, Pitch_F3), NOTE(Quarter, Pitch_Gb3), NOTE(Eighth, Pitch_Bb2), NOTE(Quarter, Pitch_Eb3), NOTE(DottedEighth, Pitch_D3), NOTE(Sixteenth, Pitch_Db3),
  NOTE(Sixteenth, Pitch_C3), NOTE(Sixteenth, Pitch_B2), NOTE(Quarter, Pitch_C3), NOTE(Eighth, Pitch_F2), NOTE(Quarter, Pitch_Ab2), NOTE(DottedEighth, Pitch_F2), NOTE(Sixteenth, Pitch_Ab2),
  NOTE(Quarter, Pitch_C3), NOTE(DottedEighth, Pitch_A2), NOTE(Sixteenth, Pitch_C3), NOTE(Half, Pitch_E3),
  synth::Note::End()
};


synth::Playback playback(synth::milliseconds(500), &notes[0]);



synth::DacMcp4725 dac;
//synth::DacPrint dac(Serial, synth::milliseconds(500));
//synth::DacPrintGraph dac(Serial, synth::milliseconds(500));

//synth::MapperLinear mapper({synth::millivolts(0), synth::millivolts(10000), synth::millivolts(0), synth::millivolts(5000)});
//synth::DacRemap(dac_inner, mapper);

synth::DigitalOut dout(8);


synth::Connection conn0(playback.Output(), dac.Input());
synth::Connection conn1(playback.GateOutput(), dout.Input());

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
