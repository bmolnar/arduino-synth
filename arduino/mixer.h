#ifndef SYNTH__MIXER_H_
#define SYNTH__MIXER_H_

#include "types.h"
#include "graph.h"

namespace synth {

class Mixer;
typedef Mixer* MixerPtr;

class MixerSignalSource : public SignalSource
{
public:
  MixerSignalSource(MixerPtr mixer) : mixer_(mixer) {}

  void Step(duration_t delta_t);
  voltage_t Value();
protected:
  MixerPtr mixer_;
};

class Mixer : public GraphObject<Mixer>
{
public:
  static const uint8_t kMaxChannels = 8;

  Mixer();
  Mixer(SignalSourcePtr input0);
  Mixer(SignalSourcePtr input0, SignalSourcePtr input1);
  Mixer(SignalSourcePtr input0, SignalSourcePtr input1, SignalSourcePtr input2);
  Mixer(SignalSourcePtr input0, SignalSourcePtr input1, SignalSourcePtr input2, SignalSourcePtr input3);
  Mixer(SignalSourcePtr input0, SignalSourcePtr input1, SignalSourcePtr input2, SignalSourcePtr input3,
        SignalSourcePtr input4);
  Mixer(SignalSourcePtr input0, SignalSourcePtr input1, SignalSourcePtr input2, SignalSourcePtr input3,
        SignalSourcePtr input4, SignalSourcePtr input5);
  Mixer(SignalSourcePtr input0, SignalSourcePtr input1, SignalSourcePtr input2, SignalSourcePtr input3,
        SignalSourcePtr input4, SignalSourcePtr input5, SignalSourcePtr input6);
  Mixer(SignalSourcePtr input0, SignalSourcePtr input1, SignalSourcePtr input2, SignalSourcePtr input3,
        SignalSourcePtr input4, SignalSourcePtr input5, SignalSourcePtr input6, SignalSourcePtr input7);

  void SetChannelInput(uint8_t channel, SignalSourcePtr input);
  void SetChannelGain(uint8_t channel, gain_t gain);
  void Step(duration_t delta_t);
  voltage_t Value();

  SignalSourcePtr Output();

protected:
  SignalSourcePtr input_[kMaxChannels]{ SignalSourcePtrNull, SignalSourcePtrNull, SignalSourcePtrNull, SignalSourcePtrNull,
                                        SignalSourcePtrNull, SignalSourcePtrNull, SignalSourcePtrNull, SignalSourcePtrNull};
  gain_t gain_[kMaxChannels]{kGainUnity, kGainUnity, kGainUnity, kGainUnity, kGainUnity, kGainUnity, kGainUnity, kGainUnity};

  MixerSignalSource output_{this};
};


} // namespace synth

#endif // SYNTH__MIXER_H_
