#ifndef SYNTH__SEQUENCER_H_
#define SYNTH__SEQUENCER_H_

#include "types.h"
#include "graph.h"

namespace synth {

class Sequencer;
typedef Sequencer* SequencerPtr;

class SequencerSignalSource : public SignalSource
{
public:
  SequencerSignalSource(SequencerPtr seq) : seq_(seq) {}
  void Step(duration_t delta_t);
  voltage_t Value();
protected:
  SequencerPtr seq_;
};

typedef voltage_t (*SequencerSlotFunction)(uint8_t);

class Sequencer : public GraphObject<Sequencer>
{
public:
  Sequencer(duration_t step_period, duty_t duty, voltage_t* slots, uint8_t num_slots);
  Sequencer(duration_t step_period, duty_t duty, SequencerSlotFunction slot_func, uint8_t num_slots);

  void Step(duration_t delta_t);
  voltage_t Value();
  bool Gate();
  SignalSourcePtr Output();

protected:
  duration_t step_period_;
  duty_t duty_;
  voltage_t* slots_ = nullptr;
  SequencerSlotFunction slot_func_ = nullptr;
  uint8_t num_slots_ = 0;
  uint8_t cur_slot_ = 0;
  duration_t step_remainder_ = 0;

  SequencerSignalSource output_{this};
};

} // namespace synth

#endif // SYNTH__SEQUENCER_H_
