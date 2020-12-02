#include "playback.h"

namespace synth {


static duration_t NoteDivToDuration(duration_t quarter_duration, const NoteDiv& div)
{
  return quarter_duration * static_cast<duration_t>(div.num) / static_cast<duration_t>(div.den);
}

Playback::Playback(duration_t quarter_duration, Note* note)
  : quarter_duration_(quarter_duration), note_(note)
{
}


void Playback::StepToPre(timestamp_t timestamp)
{
  accum_ += (timestamp - timestamp_);
  duration_t notedur;
  while (!note_->IsEnd() && (accum_ > (notedur = NoteDivToDuration(quarter_duration_, note_->div)))) {
    accum_ -= notedur;
    note_++;
  }
}
void Playback::StepToPost(timestamp_t timestamp)
{
  ((void) timestamp);
}


voltage_t Playback::Value()
{
  return ToVoltage(note_->pitch);
}
voltage_t Playback::GateValue()
{
  return (!note_->IsEnd() && accum_ < ((static_cast<duration_t>(note_->gate) * NoteDivToDuration(quarter_duration_, note_->div)) / 255)) ? millivolts(5000) : millivolts(0);
}


SignalSource& Playback::Output()
{
  return output_;
}
SignalSource& Playback::GateOutput()
{
  return gate_output_;
}


voltage_t PlaybackValueGetter::Get()
{
  return playback_.Value();
}
voltage_t PlaybackGateGetter::Get()
{
  return playback_.GateValue();
}

} // namespace synth
