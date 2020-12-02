#ifndef SYNTH__MIXER_H_
#define SYNTH__MIXER_H_

#include "macros.h"
#include "types.h"
#include "graph.h"

namespace synth {

class Mixer;
typedef Mixer* MixerPtr;

class MixerValueGetter : public SignalGetter
{
public:
  MixerValueGetter(Mixer& mixer) : mixer_(mixer) {}
  virtual voltage_t Get();
protected:
  Mixer& mixer_;
};




class MixerBase : public GraphObject<MixerBase>
{
public:
  virtual voltage_t Value() = 0;
};


class MixerBaseValueGetter : public SignalGetter
{
public:
  MixerBaseValueGetter(MixerBase& mixer) : mixer_(mixer) {}
  virtual voltage_t Get();
protected:
  MixerBase& mixer_;
};



class Mixer : public GraphObject<Mixer>
{
public:
  static const uint8_t kMaxChannels = 8;

  Mixer();
  Mixer(SignalSource& input0);
  Mixer(SignalSource& input0, SignalSource& input1);
  Mixer(SignalSource& input0, SignalSource& input1, SignalSource& input2);
  Mixer(SignalSource& input0, SignalSource& input1, SignalSource& input2, SignalSource& input3);
  Mixer(SignalSource& input0, SignalSource& input1, SignalSource& input2, SignalSource& input3,
        SignalSource& input4);
  Mixer(SignalSource& input0, SignalSource& input1, SignalSource& input2, SignalSource& input3,
        SignalSource& input4, SignalSource& input5);
  Mixer(SignalSource& input0, SignalSource& input1, SignalSource& input2, SignalSource& input3,
        SignalSource& input4, SignalSource& input5, SignalSource& input6);
  Mixer(SignalSource& input0, SignalSource& input1, SignalSource& input2, SignalSource& input3,
        SignalSource& input4, SignalSource& input5, SignalSource& input6, SignalSource& input7);

  void SetChannelInput(uint8_t channel, SignalSource& input);
  void SetChannelGain(uint8_t channel, gain_t gain);
  void StepToPre(timestamp_t timestamp);
  void StepToPost(timestamp_t timestamp);
  voltage_t Value();
  SignalSink& Input(uint8_t channel);
  SignalSource& Output();

#if GRAPH_UTILS
  uint8_t GetNumChildren();
  GraphObjectBasePtr GetChild(uint8_t index);
#endif

protected:
  gain_t gain_[kMaxChannels]{kGainUnity, kGainUnity, kGainUnity, kGainUnity, kGainUnity, kGainUnity, kGainUnity, kGainUnity};
  MixerValueGetter getter_{*this};

  SignalSink input_[kMaxChannels]{SignalSink{*this}, SignalSink{*this}, SignalSink{*this}, SignalSink{*this},
                                  SignalSink{*this}, SignalSink{*this}, SignalSink{*this}, SignalSink{*this}};
  SignalSource output_{*this, &getter_};
};










#define MIXER_N_CTOR_DEFAULT_ARGS(_n) XLIB_MAP(MIXER_N_CTOR_DEFAULT_INPUT_FN, XLIB_SEQ(_n)), XLIB_MAP(MIXER_N_CTOR_DEFAULT_GAIN_FN, XLIB_SEQ(_n)), gain_t gain_out = kGainUnity
#define MIXER_N_CTOR_DEFAULT_INPUT_FN(_i) T& XLIB_XCONCAT(input, _i)
#define MIXER_N_CTOR_DEFAULT_GAIN_FN(_i) gain_t XLIB_XCONCAT(gain, _i) = kGainUnity

#define MIXER_N_CTOR_PAIRWISE_ARGS(_n) XLIB_MAP(MIXER_N_CTOR_PAIRWISE_ARGFN, XLIB_SEQ(_n)), gain_t gain_out = kGainUnity
#define MIXER_N_CTOR_PAIRWISE_ARGFN(_i) T& XLIB_XCONCAT(input, _i), gain_t XLIB_XCONCAT(gain, _i)

#define MIXER_N_CTOR_INPUT_INIT(_n) input_{ XLIB_MAP(MIXER_N_CTOR_INPUT_FN, XLIB_SEQ(_n)) }
#define MIXER_N_CTOR_INPUT_FN(_i) SignalSink{*this, XLIB_XCONCAT(input, _i)}

#define MIXER_N_CTOR_GAIN_INIT_UNITY(_n) gain_{ XLIB_MAP(MIXER_N_CTOR_GAIN_UNITY_FN, XLIB_SEQ(_n)) }
#define MIXER_N_CTOR_GAIN_UNITY_FN(_i) kGainUnity

#define MIXER_N_CTOR_GAIN_INIT(_n) gain_{ XLIB_MAP(MIXER_N_CTOR_GAIN_FN, XLIB_SEQ(_n)) }
#define MIXER_N_CTOR_GAIN_FN(_i) XLIB_XCONCAT(gain, _i)


#define MIXER_N_CTOR_0() \
  MixerN() {}

#define MIXER_N_CTOR_1() \
  template <typename T, enable_if_t<(N == 1) && is_same<T, SignalSource>::value, bool> = true> \
  MixerN( MIXER_N_CTOR_DEFAULT_ARGS(1) ) \
    : MIXER_N_CTOR_GAIN_INIT(1), MIXER_N_CTOR_INPUT_INIT(1) \
  {}



#define MIXER_N_CTOR_DEFAULT_N(_n) \
  template <typename T, enable_if_t<(N == _n) && is_same<T, SignalSource>::value, bool> = true> \
  MixerN( MIXER_N_CTOR_DEFAULT_ARGS(_n) ) \
    : MIXER_N_CTOR_GAIN_INIT(_n), MIXER_N_CTOR_INPUT_INIT(_n), gain_out_(gain_out) \
  {}

#define MIXER_N_CTOR_PAIRWISE_N(_n) \
  template <typename T, enable_if_t<(N == _n) && is_same<T, SignalSource>::value, bool> = true> \
  MixerN( MIXER_N_CTOR_PAIRWISE_ARGS(_n) ) \
    : MIXER_N_CTOR_GAIN_INIT(_n), MIXER_N_CTOR_INPUT_INIT(_n), gain_out_(gain_out) \
  {}

/*
#define MIXER_N_CTOR_N(_n) \
  template <typename T, enable_if_t<(N == _n) && is_same<T, SignalSource>::value, bool> = true> \
  MixerN( MIXER_N_CTOR_DEFAULT_ARGS(_n) ) \
    : MIXER_N_CTOR_GAIN_INIT(_n), MIXER_N_CTOR_INPUT_INIT(_n), gain_out_(gain_out) \
  {} \
  template <typename T, enable_if_t<(N == _n) && is_same<T, SignalSource>::value, bool> = true> \
  MixerN( MIXER_N_CTOR_PAIRWISE_ARGS(_n) ) \
    : MIXER_N_CTOR_GAIN_INIT(_n), MIXER_N_CTOR_INPUT_INIT(_n), gain_out_(gain_out) \
  {}
*/
#define MIXER_N_CTOR_N(_n) \
  MIXER_N_CTOR_DEFAULT_N(_n) \
  MIXER_N_CTOR_PAIRWISE_N(_n)

#define MIXER_N_CTORS() \
  MIXER_N_CTOR_0() \
  MIXER_N_CTOR_1() \
  MIXER_N_CTOR_N(2) \
  MIXER_N_CTOR_N(3) \
  MIXER_N_CTOR_N(4) \
  MIXER_N_CTOR_N(5) \
  MIXER_N_CTOR_N(6) \
  MIXER_N_CTOR_N(7)


template <uint8_t N>
class MixerN : public MixerBase
{
public:
  static constexpr uint8_t kNumChannels = N;

  MIXER_N_CTORS()

  void SetChannelGain(uint8_t channel, gain_t gain) {
    gain_[channel % kNumChannels] = gain;
  }

  SignalSink& Input(uint8_t channel) {
    return input_[channel % kNumChannels];
  }
  SignalSource& Output() {
    return output_;
  }

  void StepToPre(timestamp_t timestamp) {
    for (uint8_t i = 0; i < kNumChannels; ++i) {
      if (input_[i].Connected()) {
        input_[i].Source()->Owner().StepTo(timestamp);
      }
    }
  }
  void StepToPost(timestamp_t timestamp) {
    ((void) timestamp);
  }

  voltage_t Value() {
    int32_t sum = 0;
    for (uint8_t i = 0; i < kNumChannels; ++i) {
      sum += input_[i].Connected() ? (static_cast<int32_t>(gain_[i]) * static_cast<int32_t>(input_[i].GetValue())) : static_cast<int32_t>(0);
    }
    return static_cast<voltage_t>((sum / static_cast<int32_t>(kGainUnity)) * static_cast<int32_t>(gain_out_) / static_cast<int32_t>(kGainUnity));
  }

#if GRAPH_UTILS
  uint8_t GetNumChildren() {
    uint8_t result = 0;
    for (uint8_t i = 0; i < kNumChannels; ++i) {
      if (input_[i].Connected()) {
        result++;
      }
    }
    return result;
  }
  GraphObjectBasePtr GetChild(uint8_t index) {
    for (uint8_t i = 0; i < kNumChannels; ++i) {
      if (input_[i].Connected() && index-- == 0) {
        return &input_[i].Source()->Owner();
      }
    }
    return nullptr;
  }
#endif

protected:
  gain_t gain_[kNumChannels] = {kGainUnity};
  MixerBaseValueGetter getter_{*this};
  SignalSink input_[kNumChannels];
  gain_t gain_out_{kGainUnity};
  SignalSource output_{*this, &getter_};
};


typedef MixerN<1> Mixer1;
typedef MixerN<2> Mixer2;
typedef MixerN<3> Mixer3;
typedef MixerN<4> Mixer4;
typedef MixerN<5> Mixer5;
typedef MixerN<6> Mixer6;
typedef MixerN<7> Mixer7;
typedef MixerN<8> Mixer8;

} // namespace synth

#endif // SYNTH__MIXER_H_
