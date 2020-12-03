#ifndef SYNTH__REMAP_H_
#define SYNTH__REMAP_H_

#include "types.h"
#include "graph.h"

namespace synth {

class Mapper
{
public:
  virtual voltage_t Map(voltage_t voltage) = 0;
};

class Remap;
typedef Remap* RemapPtr;

class RemapValueGetter : public SignalGetter
{
public:
  RemapValueGetter(Remap& remap) : remap_(remap) {}
  virtual voltage_t Get();
protected:
  Remap& remap_;
};

class Remap : public GraphObject<Remap>
{
public:
  Remap(Mapper& mapper);
  Remap(Mapper& mapper, SignalSource& input);
  void StepToPre(timestamp_t timestamp);
  void StepToPost(timestamp_t timestamp);
  voltage_t Value();
  SignalSink& Input();
  SignalSource& Output();

#if GRAPH_UTILS
  uint8_t GetNumChildren();
  GraphObjectBasePtr GetChild(uint8_t index);
#endif

  Mapper& mapper_;
  RemapValueGetter getter_{*this};
  SignalSink input_{*this};
  SignalSource output_{*this, &getter_};
};




struct RemapLinearParams
{
  voltage_t in_min;
  voltage_t in_max;
  voltage_t out_min;
  voltage_t out_max;
};

static inline voltage_t RemapVoltage(const RemapLinearParams& params, voltage_t voltage)
{
  return static_cast<voltage_t>(static_cast<int32_t>(params.out_min) +  ((static_cast<int32_t>(voltage) - static_cast<int32_t>(params.in_min)) * (static_cast<int32_t>(params.out_max) - static_cast<int32_t>(params.out_min)) / (static_cast<int32_t>(params.in_max) - static_cast<int32_t>(params.in_min))));
}

class MapperLinear : public Mapper
{
public:
  MapperLinear(const RemapLinearParams& params) : params_(params) {}
  voltage_t Map(voltage_t voltage) { return RemapVoltage(params_, voltage); }
protected:
  RemapLinearParams params_;
};

class RemapLinear : public Remap
{
public:
  RemapLinear(const RemapLinearParams& params) : Remap(linear_), linear_(params) {}
  RemapLinear(const RemapLinearParams& params, SignalSource& input) : Remap(linear_, input), linear_(params) {}
protected:
  MapperLinear linear_;
};


} // namespace synth

#endif // SYNTH__REMAP_H_
