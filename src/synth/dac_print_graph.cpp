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


void DacPrintGraph::PrintHoriz(voltage_t value)
{
  int32_t rpos32 = 30 + (30 * static_cast<int32_t>(value) / 4000.0);
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

