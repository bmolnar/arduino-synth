#include <synth.h>

namespace pitch = synth::pitch;

synth::voltage_t slots0[] = {
  ToVoltage(pitch::Pitch_E2), ToVoltage(pitch::Pitch_G2), ToVoltage(pitch::Pitch_A2), ToVoltage(pitch::Pitch_G2),
  ToVoltage(pitch::Pitch_D3), ToVoltage(pitch::Pitch_C3), ToVoltage(pitch::Pitch_D3), ToVoltage(pitch::Pitch_E3)
};

synth::voltage_t slots1[] = {
  ToVoltage(pitch::Pitch_C3), ToVoltage(pitch::Pitch_C2), ToVoltage(pitch::Pitch_C2), ToVoltage(pitch::Pitch_C3),
  ToVoltage(pitch::Pitch_C2), ToVoltage(pitch::Pitch_C2), ToVoltage(pitch::Pitch_Bb2), ToVoltage(pitch::Pitch_C2)
};


synth::Sequencer seq(synth::milliseconds(128), synth::kDutyHalf, slots0, 8);

synth::DacMcp4725 dac;
//synth::DacPrint dac(Serial, synth::milliseconds(500));
//synth::DacPrintGraph dac(Serial, remap.Output(), synth::milliseconds(500));

synth::MapperLinear mapper({synth::millivolts(0), synth::millivolts(10000), synth::millivolts(0), synth::millivolts(5000)});
//synth::DacRemap dac(dac_inner, mapper);

synth::DigitalOut dout(8);


synth::Connection conn0(seq.Output(), dac.Input());
synth::Connection conn1(seq.GateOutput(), dout.Input());

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
