#ifndef SYNTH__MIXER_H_
#define SYNTH__MIXER_H_

#include "types.h"
#include "graph.h"

namespace synth {

class Mixer;
typedef Mixer* MixerPtr;

class MixerValueGetter : public SignalGetter
{
public:
  MixerValueGetter(MixerPtr mixer) : mixer_(mixer) {}
  virtual voltage_t Get();
protected:
  MixerPtr mixer_;
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

  void StepPre(duration_t delta_t);
  void StepPost(duration_t delta_t);

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
/*
  SignalSourcePtr input_[kMaxChannels]{ SignalSourcePtrNull, SignalSourcePtrNull, SignalSourcePtrNull, SignalSourcePtrNull,
                                        SignalSourcePtrNull, SignalSourcePtrNull, SignalSourcePtrNull, SignalSourcePtrNull};
*/
  gain_t gain_[kMaxChannels]{kGainUnity, kGainUnity, kGainUnity, kGainUnity, kGainUnity, kGainUnity, kGainUnity, kGainUnity};
  MixerValueGetter getter_{this};

  SignalSink input_[kMaxChannels]{SignalSink{*this}, SignalSink{*this}, SignalSink{*this}, SignalSink{*this},
                                  SignalSink{*this}, SignalSink{*this}, SignalSink{*this}, SignalSink{*this}};
  SignalSource output_{*this, &getter_};
};


} // namespace synth

#endif // SYNTH__MIXER_H_
