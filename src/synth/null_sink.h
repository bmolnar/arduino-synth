#ifndef SYNTH__NULL_SINK_H_
#define SYNTH__NULL_SINK_H_

#include "types.h"
#include "graph.h"

namespace synth {

class NullSink : public GraphObject<NullSink>
{
public:
  NullSink();
  NullSink(SignalSource& source);
  SignalSink& Input();
  void StepToPre(timestamp_t timestamp);
  void StepToPost(timestamp_t timestamp);

#if GRAPH_UTILS
  uint8_t GetNumChildren();
  GraphObjectBasePtr GetChild(uint8_t index);
#endif

protected:
  SignalSink input_;
};

} // namespace synth

#endif // SYNTH__NULL_SINK_H_
