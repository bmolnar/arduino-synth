#include "dac_print_graph.h"

namespace synth {


static constexpr uint8_t UNumWidth(uint32_t value)
{
  return ((value < 1000000000) ? ((value < 100000000) ? ((value < 10000000) ? ((value < 1000000) ? ((value < 100000) ? ((value < 10000) ? ((value < 1000) ? ((value < 100) ? ((value < 10) ? 1 : 2) : 3) : 4) : 5) : 6) : 7) : 8) : 9) : 10);
}
static constexpr uint8_t NumWidth(int32_t value)
{
  return ((value < 0) ? 1 : 0) + UNumWidth(static_cast<uint32_t>((value >= 0) ? value : -value));
}



DacPrintGraph::DacPrintGraph(Print& print, duration_t sample_period)
 : print_(print), sample_period_(sample_period), sample_accum_(sample_period)
{
}
DacPrintGraph::DacPrintGraph(Print& print, SignalSource& source, duration_t sample_period)
 : print_(print), sample_period_(sample_period), sample_accum_(sample_period)
{
  input_.Connect(source);
}
void DacPrintGraph::Begin()
{
  printcnt_ = 0;
  print_.println();
  print_.println();
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
  PrintSpaces(kLeftWidth);

  print_.print(" | ");
  // 81
  print_.print("4    -    3    -    2    -    1    -    0    -    1    -    2    -    3    -    4");

  print_.print(" | ");

  PrintSpaces(kRightWidth);

  print_.println();
}
void DacPrintGraph::PrintHoriz(voltage_t value, timestamp_t timestamp)
{
  if ((printcnt_++ % 40) == 0) {
    PrintScaleLine();
  }

  int32_t rpos32 = 40 + (40 * static_cast<int32_t>(value) / 4000);
  uint8_t rpos = static_cast<uint8_t>((rpos32 < 0) ? 0 : ((rpos32 > 80) ? 80 : rpos32));

  timestamp_t ts_millis = timestamp / 1000;
  uint8_t ts_digits = UNumWidth(ts_millis);
  print_.print(ts_millis);
  PrintSpaces(kLeftWidth - ts_digits);

  print_.print(" | ");

  PrintSpaces(rpos);
  print_.print('+');
  PrintSpaces((kMiddleWidth - 1) - rpos);

  print_.print(" | ");

  uint8_t val_digits = NumWidth(value);
  print_.print(value);
  PrintSpaces(kRightWidth - val_digits);
  print_.println();
}
void DacPrintGraph::StepToPre(timestamp_t timestamp)
{
  // This calls SetVoltage
  Dac::StepToPre(timestamp);

  last_timestamp_ = timestamp;

  duration_t delta_t = (timestamp - timestamp_);
  sample_accum_ += delta_t;
  if (sample_accum_ >= sample_period_) {
    PrintHoriz(last_value_, last_timestamp_);
    sample_accum_ = sample_accum_ % sample_period_;
  }
}
void DacPrintGraph::StepToPost(timestamp_t timestamp)
{
  ((void) timestamp);
}
void DacPrintGraph::SetVoltage(voltage_t voltage)
{
  last_value_ = voltage;
}

} // namespace synth

