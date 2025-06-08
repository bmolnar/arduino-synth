#ifndef SYNTH__SEQUENCER_H_
#define SYNTH__SEQUENCER_H_

#include "types.h"
#include "graph.h"

namespace synth {

class Sequencer;
typedef Sequencer* SequencerPtr;
typedef voltage_t (*SequencerSlotFunction)(uint8_t);


/**
 * SequencerValueGetter
 */
class SequencerValueGetter : public SignalGetter
{
public:
  SequencerValueGetter(SequencerPtr seq) : seq_(seq) {}
  virtual voltage_t Get();
protected:
  SequencerPtr seq_;
};


/**
 * SequencerGateGetter
 */
class SequencerGateGetter : public SignalGetter
{
public:
  SequencerGateGetter(SequencerPtr seq) : seq_(seq) {}
  virtual voltage_t Get();
protected:
  SequencerPtr seq_;
};


/**
 * Sequencer
 *
 * Functions as a synth sequencer, providing a repeating sequence of CV/Gate
 * signals
 */
class Sequencer : public GraphObject<Sequencer>
{
public:
  /**
   * Initializes a sequencer object with a given step period, gate duration and
   * CV sequence given as an array of values
   *
   * @param step_period The duration of each step, in microseconds
   * @param duty The fraction of each step period for which the gate output is
   *             high
   * @param slots A pointer to an array of `voltage_t` values
   * @param num_slots The size of the `slots` array
   */
  Sequencer(duration_t step_period, duty_t duty, voltage_t* slots, uint8_t num_slots);

  /**
   * Initializes a sequencer object with a given step period, gate duration and
   * a function that returns a CV value for each slot index
   *
   * @param step_period The duration of each step, in microseconds
   * @param duty The fraction of each step period for which the gate output is
   *             high
   * @param slot_func A function that returns a `voltage_t` for each slot index
   **                 (given as a uint8_t)
   * @param num_slots The number of slots to be used by the sequencer
   */
  Sequencer(duration_t step_period, duty_t duty, SequencerSlotFunction slot_func, uint8_t num_slots);

  /**
   * Gets the current value of the CV output signal
   *
   * @return The current value of the CV output signal, in Volts
   */
  voltage_t Value();

  /**
   * Gets a `SignalSource` object representing the CV output signal
   *
   * This can be connected to a `SignalSink` object using a `Connection` object
   *
   * @return A reference to a `SignalSource` object representing the CV output
   *         signal
   */
  SignalSource& Output();

  /**
   * Gets the current value of the gate output signal
   *
   * @return The current value of the gate signal, in Volts
   */
  voltage_t GateValue();

  /**
   * Gets a `SignalSource` object representing the gate output signal
   *
   * This can be connected to a `SignalSink` object using a `Connection` object
   *
   * @return A reference to a `SignalSource` object representing the gate output
   *         signal
   */
  SignalSource& GateOutput();

  /**
   * Called by run graph just before `StepTo`
   *
   * @param timestamp The time stamp provided in the `StepTo` call
   */
  void StepToPre(timestamp_t timestamp);

  /**
   * Called by run graph just after `StepTo`
   *
   * @param timestamp The time stamp provided in the `StepTo` call
   */
  void StepToPost(timestamp_t timestamp);

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
