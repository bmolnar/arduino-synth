#ifndef SYNTH__SEQUENCER_H_
#define SYNTH__SEQUENCER_H_

#include "types.h"
#include "graph.h"

namespace synth {

class Sequencer;
typedef Sequencer* SequencerPtr;

typedef voltage_t (*SequencerSlotFunction)(uint8_t);


class SequencerValueGetter : public SignalGetter
{
public:
  SequencerValueGetter(SequencerPtr seq) : seq_(seq) {}
  virtual voltage_t Get();
protected:
  SequencerPtr seq_;
};
class SequencerGateGetter : public SignalGetter
{
public:
  SequencerGateGetter(SequencerPtr seq) : seq_(seq) {}
  virtual voltage_t Get();
protected:
  SequencerPtr seq_;
};


class Sequencer : public GraphObject<Sequencer>
{
public:
  Sequencer(duration_t step_period, duty_t duty, voltage_t* slots, uint8_t num_slots);
  Sequencer(duration_t step_period, duty_t duty, SequencerSlotFunction slot_func, uint8_t num_slots);

  void StepPre(duration_t delta_t);
  void StepPost(duration_t delta_t);

  void StepToPre(timestamp_t timestamp);
  void StepToPost(timestamp_t timestamp);

  voltage_t Value();
  voltage_t GateValue();
  SignalSource& Output();
  SignalSource& GateOutput();

protected:
  duration_t step_period_;
  duty_t duty_;
  voltage_t* slots_ = nullptr;
  SequencerSlotFunction slot_func_ = nullptr;
  uint8_t num_slots_ = 0;
  uint8_t cur_slot_ = 0;
  duration_t step_remainder_ = 0;

  SequencerValueGetter getter_{this};
  SequencerGateGetter gate_getter_{this};

  SignalSource output_{*this, &getter_};
  SignalSource gate_output_{*this, &gate_getter_};
};

} // namespace synth

#endif // SYNTH__SEQUENCER_H_
