#ifndef SYNTH__REMAP_H_
#define SYNTH__REMAP_H_

#include "types.h"
#include "graph.h"

namespace synth {

// Forward declarations
class Remap;
typedef Remap* RemapPtr;


//
// Mapper Definitions
//

/**
 * Mapper
 *
 * Class containing a method Map that maps values
 */
class Mapper
{
public:
  /**
   * Maps voltage values to other voltage values
   *
   * @param voltage Input voltage value (in mV)
   * @return Output voltage value (in mV)
   */
  virtual voltage_t Map(voltage_t voltage) = 0;
};


//
// Remap Definitions
//

/**
 * RemapValueGetter
 *
 * SignalGetter for Remap component
 */
class RemapValueGetter : public SignalGetter
{
public:
  RemapValueGetter(Remap& remap) : remap_(remap) {}
  virtual voltage_t Get();
protected:
  Remap& remap_;
};


/**
 * Remap
 *
 * A component that applies a Mapper to a signal
 */
class Remap : public GraphObject<Remap>
{
public:

  /**
   * Initializes this component with a given Mapper
   *
   * @param mapper A refernce to a Mapper object
   */
  Remap(Mapper& mapper);

  /**
   * Initializes this component with a given Mapper and connects the given
   * SignalSource to its input
   *
   * @param mapper A refernce to a Mapper object
   * @param input A SignalSource that will be connected to this component's
   *              input
   */
  Remap(Mapper& mapper, SignalSource& input);

  /**
   * Gets the current value of the output signal
   *
   * @return The current value of the output signal, in mV
   */
  voltage_t Value();

  /**
   * Gets a reference to the SignalSink for the input
   *
   * @return A reference to the SignalSink of the input
   */
  SignalSink& Input();

  /**
   * Gets a reference to the SignalSource for the output signal
   *
   * @return A reference to the SignalSource of the output
   */
  SignalSource& Output();

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

#if GRAPH_UTILS
  uint8_t GetNumChildren();
  GraphObjectBasePtr GetChild(uint8_t index);
#endif // GRAPH_UTILS

//protected:
  Mapper& mapper_;
  RemapValueGetter getter_{*this};
  SignalSink input_{*this};
  SignalSource output_{*this, &getter_};
};


//
// RemapLinear Definitions
//

struct RemapLinearParams
{
  voltage_t in_min;
  voltage_t in_max;
  voltage_t out_min;
  voltage_t out_max;
};

static inline voltage_t RemapVoltage(const RemapLinearParams& params, voltage_t voltage)
{
  return static_cast<voltage_t>(
      static_cast<int32_t>(params.out_min)
        + ((static_cast<int32_t>(voltage) - static_cast<int32_t>(params.in_min))
          *  (static_cast<int32_t>(params.out_max) - static_cast<int32_t>(params.out_min))
             / (static_cast<int32_t>(params.in_max) - static_cast<int32_t>(params.in_min))));
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
