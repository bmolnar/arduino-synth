#ifndef SYNTH__REMAP_H_
#define SYNTH__REMAP_H_

#include "types.h"
#include "graph.h"

namespace synth {

struct RemapParams
{
  voltage_t in_min;
  voltage_t in_max;
  voltage_t out_min;
  voltage_t out_max;
};

class Remap;
typedef Remap* RemapPtr;

class RemapValueGetter : public SignalGetter
{
public:
  RemapValueGetter(RemapPtr remap) : remap_(remap) {}
  virtual voltage_t Get();
protected:
  RemapPtr remap_;
};

class Remap : public GraphObject<Remap>
{
public:
  Remap(const RemapParams& params);
  Remap(const RemapParams& params, SignalSource& input0);
  void StepToPre(timestamp_t timestamp);
  void StepToPost(timestamp_t timestamp);
  voltage_t Value();
  SignalSink& Input();
  SignalSource& Output();

#if GRAPH_UTILS
  uint8_t GetNumChildren();
  GraphObjectBasePtr GetChild(uint8_t index);
#endif

protected:
  RemapParams params_;
  RemapValueGetter getter_{this};
  SignalSink input_{*this};
  SignalSource output_{*this, &getter_};
};


} // namespace synth

#endif // SYNTH__REMAP_H_
