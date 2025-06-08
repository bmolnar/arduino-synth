#ifndef SYNTH__PLAYBACK_H_
#define SYNTH__PLAYBACK_H_

#include "types.h"
#include "graph.h"
#include "notes.h"

namespace synth {

// Forward declarations
class Playback;
typedef Playback* PlaybackPtr;


/**
 * NoteDiv
 *
 * A struct representing the value of a musical note (e.g. quarter note, half
 * note)
 *
 * This is expressed as a multiple of a quarter note's value and is given as a
 * ratio between two integers, num and den. Thus, a quarter note has values
 * num=1 and den=1, and a dotted quarter note has values num=3 and den=2, since
 * it is 1.5x the duration of a quarter note.
 */
struct NoteDiv
{
  uint8_t num;
  uint8_t den;

  bool operator==(const NoteDiv& rhs) const { return (num == rhs.num) && (den == rhs.den); }
};

static constexpr NoteDiv kWholeNote{4, 1};
static constexpr NoteDiv kHalfNote{2, 1};
static constexpr NoteDiv kDottedHalfNote{3, 1};
static constexpr NoteDiv kQuarterNote{1, 1};
static constexpr NoteDiv kDottedQuarterNote{3, 2};
static constexpr NoteDiv kEighthNote{1, 2};
static constexpr NoteDiv kDottedEighthNote{3, 4};
static constexpr NoteDiv kSixteenthNote{1, 4};
static constexpr NoteDiv kDottedSixteenthNote{3, 8};
static constexpr NoteDiv kEndNote{0, 0};

/**
 * Note
 *
 * A struct representing a musical note, with a value, duration and pitch
 */
struct Note
{
  NoteDiv div;
  uint8_t gate;
  Pitch pitch;

  /**
   * Creates a legato note with a given value and pitch
   *
   * A legato note has duration (gate) of 255/255.
   *
   * @param div The value of the note, expressed as a NoteDiv
   * @param patch The pitch of the note
   * @return The resulting Note struct
   */
  static constexpr Note Legato(const NoteDiv& div, const Pitch& pitch)
  {
    return Note{div, 255, pitch};
  }

  /**
   * Creates a normal note with a given value and pitch
   *
   * A normal note has duration (gate) of 192/255.
   *
   * @param div The value of the note, expressed as a NoteDiv
   * @param patch The pitch of the note
   * @return The resulting Note struct
   */
  static constexpr Note Normal(const NoteDiv& div, const Pitch& pitch)
  {
    return Note{div, 192, pitch};
  }

  /**
   * Creates a rest with a given value
   *
   * A rest has duration (gate) of 0/255.
   *
   * @param div The value of the rest, expressed as a NoteDiv
   * @return The resulting Note struct
   */
  static constexpr Note Rest(const NoteDiv& div)
  {
    return Note{div, 0, Pitch{0}};
  }

  /**
   * Creates a special "end" note, which signifies the end of a sequence
   *
   * @return The resulting Note struct
   */
  static constexpr Note End()
  {
    return Note{kEndNote, 0, Pitch{0}};
  }

  /**
   * Checks if Note object is an "end" note. 
   */
  bool IsEnd() { return div == kEndNote; }
};


/**
 * PlaybackValueGetter
 */
class PlaybackValueGetter : public SignalGetter
{
public:
  PlaybackValueGetter(Playback& playback) : playback_(playback) {}
  virtual voltage_t Get();
protected:
  Playback& playback_;
};


/**
 * PlaybackGateGetter
 */
class PlaybackGateGetter : public SignalGetter
{
public:
  PlaybackGateGetter(Playback& playback) : playback_(playback) {}
  virtual voltage_t Get();
protected:
  Playback& playback_;
};


/**
 * Playback
 *
 * Plays a sequence of notes at a given tempo and provides CV/Gate output
 */
class Playback : public GraphObject<Playback>
{
public:

  /**
   * Initializes object with given tempo and note sequence
   *
   * @param quarter_duration The durtion of a quarter note, in microseconds
   * @param note A pointer to an array of Note structs. This array must end
   *             with an end note.
   */
  Playback(duration_t quarter_duration, Note* note);

  /**
   * Gets the current value of the CV output signal
   *
   * @return The current value of the CV output signal, in mV
   */
  voltage_t Value();

  /**
   * Gets a reference to the SignalSource for the CV output signal
   *
   * @return A reference to a SignalSource of the CV output signal
   */
  SignalSource& Output();

  /**
   * Gets the current value of the gate output signal
   *
   * @return The current value of the gate signal, in mV
   */
  voltage_t GateValue();

  /**
   * Gets a reference to the SignalSource for the gate output signal
   *
   * @return A reference to a SignalSource of the gate output signal
   */
  SignalSource& GateOutput();

  /**
   * Called by run graph just before StepTo
   *
   * @param timestamp The time stamp provided in the StepTo call
   */
  void StepToPre(timestamp_t timestamp);

  /**
   * Called by run graph just after StepTo
   *
   * @param timestamp The time stamp provided in the StepTo call
   */
  void StepToPost(timestamp_t timestamp);

protected:
  duration_t quarter_duration_;
  Note* note_;
  duration_t accum_{0};

  PlaybackValueGetter getter_{*this};
  PlaybackGateGetter gate_getter_{*this};
  SignalSource output_{*this, &getter_};
  SignalSource gate_output_{*this, &gate_getter_};
};

} // namespace synth

#endif // SYNTH__PLAYBACK_H_
