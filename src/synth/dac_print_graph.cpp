#include "dac_print_graph.h"

namespace synth {

DacPrintGraph::DacPrintGraph(Print& print, duration_t sample_period)
 : print_(print), sample_period_(sample_period)
{
}
DacPrintGraph::DacPrintGraph(Print& print, SignalSource& source, duration_t sample_period)
 : print_(print), sample_period_(sample_period)
{
  input_.Connect(source);
}

void DacPrintGraph::Begin()
{

}


void DacPrintGraph::PrintSpaces(uint8_t spaces)
{
  while (spaces-- > 0) {
    print_.print(" ");
  }
}

// [0, 8, 16, 24, 32, 40, 48, 56, 64]
// [0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64]
//
void DacPrintGraph::PrintScaleLine()
{
  print_.println("        4    -    3    -    2    -    1    -    0    -    1    -    2    -    3    -    4");

}
void DacPrintGraph::PrintHoriz(voltage_t value)
{

  if ((printcnt_++ % 40) == 0) {
    PrintScaleLine();
  }

  int32_t rpos32 = 40 + (40 * static_cast<int32_t>(value) / 4000.0);

  uint8_t digits =  ((value < 10000) ? ((value < 1000) ? ((value < 100) ? ((value < 10) ? 1 : 2) : 3) : 4) : 5);
  print_.print(value); uint8_t rest = 8 - digits; while (rest-- > 0) { print_.print(" "); };

  uint16_t rpos = static_cast<uint16_t>(rpos32);
  while (rpos-- > 0) {
    print_.print(" ");
  }
  print_.println(".");
}

void DacPrintGraph::StepPre(duration_t delta_t)
{
  // This calls SetVoltage
  Dac::StepPre(delta_t);

  sample_accum_ += delta_t;
  if (sample_accum_ >= sample_period_) {
    PrintHoriz(last_value_);
    sample_accum_ = sample_accum_ % sample_period_;
  }
}
void DacPrintGraph::StepPost(duration_t delta_t)
{
}





void DacPrintGraph::StepToPre(timestamp_t timestamp)
{
  // This calls SetVoltage
  Dac::StepToPre(timestamp);

  duration_t delta_t = (timestamp - timestamp_);
  sample_accum_ += delta_t;
  if (sample_accum_ >= sample_period_) {
    PrintHoriz(last_value_);
    sample_accum_ = sample_accum_ % sample_period_;
  }
}
void DacPrintGraph::StepToPost(timestamp_t timestamp)
{
}



void DacPrintGraph::SetVoltage(voltage_t voltage)
{
  last_value_ = voltage;
}

} // namespace synth

