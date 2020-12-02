#include <synth.h>

namespace note = synth::notes::voltage;

synth::voltage_t slots0[] = {
  note::Note_E2, note::Note_G2, note::Note_A2, note::Note_G2,
  note::Note_D3, note::Note_C3, note::Note_D3, note::Note_E3
};

synth::voltage_t slots1[] = {
  note::Note_C3, note::Note_C2, note::Note_C2, note::Note_C3,
  note::Note_C2, note::Note_C2, note::Note_Bb2, note::Note_C2
};


synth::Sequencer seq(synth::milliseconds(128), synth::kDutyHalf, slots1, 8);

//synth::Remap remap({synth::millivolts(-10000), synth::millivolts(10000), synth::millivolts(0), synth::millivolts(5000)});
//synth::Remap remap({synth::millivolts(0), synth::millivolts(5000), synth::millivolts(0), synth::millivolts(5000)});
synth::Remap remap({synth::millivolts(0), synth::millivolts(10000), synth::millivolts(0), synth::millivolts(5000)});

synth::DacMcp4725 dac;
//synth::DacPrint dac(Serial, synth::milliseconds(500));

synth::DigitalOut dout(8);

synth::Connection conn0(seq.Output(), remap.Input());
synth::Connection conn1(remap.Output(), dac.Input());
synth::Connection conn2(seq.GateOutput(), dout.Input());

synth::Timer timer;
synth::timestamp_t g_timestamp = 0;

void setup() {
  Serial.begin(9600);
  timer.Start();
  dac.Begin();
}

void loop() {
  synth::duration_t delta_t = timer.ElapsedSinceLast();
  g_timestamp += delta_t;

  dac.StepTo(g_timestamp);
  dout.StepTo(g_timestamp);
}
