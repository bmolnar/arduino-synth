#ifndef SYNTH__NULL_SINK_H_
#define SYNTH__NULL_SINK_H_

#include "types.h"
#include "graph.h"

namespace synth {

/**
 * NullSink
 *
 * Provides a `SignalSink` object that discards the signal
 */
class NullSink : public GraphObject<NullSink>
{
public:

  /**
   * Initializes object
   */
  NullSink();

  /**
   * Initializes object and connects to a given `SignalSource` object
   *
   * @param source The `SignalSource` object that provides input to this
   *               component
   */
  NullSink(SignalSource& source);

  /**
   * Gets input as a `SignalSink` object
   *
   * @return A reference to the input `SignalSink` object
   */
  SignalSink& Input();

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

#if GRAPH_UTILS
  uint8_t GetNumChildren();
  GraphObjectBasePtr GetChild(uint8_t index);
#endif // GRAPH_UTILS

protected:
  SignalSink input_;
};

} // namespace synth

#endif // SYNTH__NULL_SINK_H_
