#include "sequencer.h"

namespace synth {

//
// Sequencer
//
Sequencer::Sequencer(duration_t step_period, duty_t duty, voltage_t* slots, uint8_t num_slots)
    : step_period_(step_period), duty_(duty), slots_(slots), slot_func_(nullptr), num_slots_(num_slots)
{
}
Sequencer::Sequencer(duration_t step_period, duty_t duty, SequencerSlotFunction slot_func, uint8_t num_slots)
    : step_period_(step_period), duty_(duty), slots_(nullptr), slot_func_(slot_func), num_slots_(num_slots)
{
}

void Sequencer::StepToPre(timestamp_t timestamp)
{
  duration_t delta_t = timestamp - timestamp_;
  duration_t new_remainder = step_remainder_ + delta_t;
  cur_slot_ = (cur_slot_ + static_cast<uint8_t>(new_remainder / step_period_)) % num_slots_;
  step_remainder_ = new_remainder % step_period_;
}
void Sequencer::StepToPost(timestamp_t timestamp)
{
  ((void) timestamp);
}


voltage_t Sequencer::Value()
{
  return (slots_ != nullptr) ? slots_[cur_slot_] : (*slot_func_)(cur_slot_);
}
voltage_t Sequencer::GateValue()
{
  duration_t gate_duration = step_period_ * static_cast<duration_t>(duty_) / 255;
  return (step_remainder_ <= gate_duration) ? millivolts(5000) : millivolts(0);
}
SignalSource& Sequencer::Output()
{
  return output_;
}
SignalSource& Sequencer::GateOutput()
{
  return gate_output_;
}

//
// SequenceValueGetter
//
voltage_t SequencerValueGetter::Get()
{
  return seq_->Value();
}

//
// SequenceGateGetter
//
voltage_t SequencerGateGetter::Get()
{
  return seq_->GateValue();
}

} // namespace synth
