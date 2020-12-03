#ifndef SYNTH__PLAYBACK_H_
#define SYNTH__PLAYBACK_H_

#include "types.h"
#include "graph.h"
#include "notes.h"

namespace synth {

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

struct Note
{
  NoteDiv div;
  uint8_t gate;
  Pitch pitch;

  bool IsEnd() { return div == kEndNote; }

  static constexpr Note Legato(const NoteDiv& div, const Pitch& pitch)
  {
    return Note{div, 255, pitch};
  }
  static constexpr Note Normal(const NoteDiv& div, const Pitch& pitch)
  {
    return Note{div, 192, pitch};
  }
  static constexpr Note Rest(const NoteDiv& div)
  {
    return Note{div, 0, Pitch{0}};
  }
  static constexpr Note End()
  {
    return Note{kEndNote, 0, Pitch{0}};
  }
};




class Playback;
typedef Playback* PlaybackPtr;


class PlaybackValueGetter : public SignalGetter
{
public:
  PlaybackValueGetter(Playback& playback) : playback_(playback) {}
  virtual voltage_t Get();
protected:
  Playback& playback_;
};
class PlaybackGateGetter : public SignalGetter
{
public:
  PlaybackGateGetter(Playback& playback) : playback_(playback) {}
  virtual voltage_t Get();
protected:
  Playback& playback_;
};


class Playback : public GraphObject<Playback>
{
public:
  Playback(duration_t quarter_duration, Note* note);

  void StepToPre(timestamp_t timestamp);
  void StepToPost(timestamp_t timestamp);

  voltage_t Value();
  voltage_t GateValue();
  SignalSource& Output();
  SignalSource& GateOutput();

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
