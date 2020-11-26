#include "sequencer.h"

namespace synth {

Sequencer::Sequencer(duration_t step_period, duty_t duty, voltage_t* slots, uint8_t num_slots)
    : step_period_(step_period), duty_(duty), slots_(slots), slot_func_(nullptr), num_slots_(num_slots)
{
}
Sequencer::Sequencer(duration_t step_period, duty_t duty, SequencerSlotFunction slot_func, uint8_t num_slots)
    : step_period_(step_period), duty_(duty), slots_(nullptr), slot_func_(slot_func), num_slots_(num_slots)
{
}

void Sequencer::Step(duration_t delta_t)
{
  duration_t new_remainder = step_remainder_ + delta_t;
  cur_slot_ = (cur_slot_ + static_cast<uint8_t>(new_remainder / step_period_)) % num_slots_;
  step_remainder_ = new_remainder % step_period_;
}
voltage_t Sequencer::Value()
{
  return (slots_ != nullptr) ? slots_[cur_slot_] : (*slot_func_)(cur_slot_);
}
bool Sequencer::Gate()
{
  return step_remainder_ <= (step_period_ * duty_ / 255);
}
SignalSourcePtr Sequencer::Output()
{
  return &output_;
}


void SequencerSignalSource::Step(duration_t delta_t)
{
  seq_->Step(delta_t);
}
voltage_t SequencerSignalSource::Value()
{
  return seq_->Value();
}


} // namespace synth
