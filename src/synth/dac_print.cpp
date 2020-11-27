#include "dac_print.h"

namespace synth {

DacPrint::DacPrint(Print& print, duration_t flush_period)
 : print_(print), flush_period_(flush_period)
{
}
DacPrint::DacPrint(Print& print, SignalSource& source, duration_t flush_period)
 : print_(print), flush_period_(flush_period)
{
  input_.Connect(source);
}

void DacPrint::Begin()
{
  ResetStats(stats_);
}

void DacPrint::PrintStats(const DacPrintStats& stats)
{
  print_.print("last=");
  print_.print(stats.last_value);
  print_.print(",min=");
  print_.print(stats.min_value);
  print_.print(",max=");
  print_.print(stats.max_value);
  print_.print(",count=");
  print_.print(stats.updates);
  print_.print(",avg=");
  print_.print(stats.accum_sum / static_cast<int32_t>(stats.updates));
  print_.print(",var=");
  print_.print(stats.accum_sum_sq / stats.updates);
  print_.print(",period=");
  print_.print(stats.accum_time / stats.updates);
  print_.println();
}
void DacPrint::ResetStats(DacPrintStats& stats)
{
  stats.min_value = kVoltageMax;
  stats.max_value = kVoltageMin;
  stats.last_value = 0;
  stats.accum_sum = 0;
  stats.accum_sum_sq = 0;
  stats.accum_time = 0;
  stats.updates = 0;
}



void DacPrint::StepPre(duration_t delta_t)
{
  // This calls SetVoltage
  Dac::StepPre(delta_t);

  stats_.accum_time += delta_t;
  flush_accum_ += delta_t;
  if (flush_accum_ >= flush_period_) {
    PrintStats(stats_);
    ResetStats(stats_);
    flush_accum_ = flush_accum_ % flush_period_;
  }
}
void DacPrint::StepPost(duration_t delta_t)
{
}





void DacPrint::StepToPre(timestamp_t timestamp)
{
  // This calls SetVoltage
  Dac::StepToPre(timestamp);

  duration_t delta_t = (timestamp - timestamp_);
  stats_.accum_time += delta_t;
  flush_accum_ += delta_t;
  if (flush_accum_ >= flush_period_) {
    PrintStats(stats_);
    ResetStats(stats_);
    flush_accum_ = flush_accum_ % flush_period_;
  }
}
void DacPrint::StepToPost(timestamp_t timestamp)
{
}



void DacPrint::SetVoltage(voltage_t voltage)
{
  stats_.last_value = voltage;
  if (voltage > stats_.max_value) {
    stats_.max_value = voltage;
  }
  if (voltage < stats_.min_value) {
    stats_.min_value = voltage;
  }
  stats_.accum_sum += voltage;
  stats_.accum_sum_sq += (voltage * voltage);
  stats_.updates++;
}

} // namespace synth

