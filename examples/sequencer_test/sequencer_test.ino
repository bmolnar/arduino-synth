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


synth::Sequencer seq(synth::milliseconds(128), synth::kDutyHalf, slots1, 8);

//synth::Remap remap({synth::millivolts(-10000), synth::millivolts(10000), synth::millivolts(0), synth::millivolts(5000)});
//synth::Remap remap({synth::millivolts(0), synth::millivolts(5000), synth::millivolts(0), synth::millivolts(5000)});
synth::Remap remap({synth::millivolts(0), synth::millivolts(10000), synth::millivolts(0), synth::millivolts(5000)});

synth::DacMcp4725 dac;
//synth::DacPrint dac(Serial, synth::milliseconds(500));
//synth::DacPrintGraph dac(Serial, synth::milliseconds(500));

synth::DigitalOut dout(8);

synth::Connection conn0(seq.Output(), remap.Input());
synth::Connection conn1(remap.Output(), dac.Input());
synth::Connection conn2(seq.GateOutput(), dout.Input());

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
