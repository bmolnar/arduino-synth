#include "mixer.h"

namespace synth {

Mixer::Mixer()
  : input_{ SignalSourcePtrNull,  SignalSourcePtrNull,  SignalSourcePtrNull,  SignalSourcePtrNull,  SignalSourcePtrNull,  SignalSourcePtrNull,  SignalSourcePtrNull,  SignalSourcePtrNull}
{
}
Mixer::Mixer(SignalSourcePtr input0)
  : input_{input0,  SignalSourcePtrNull,  SignalSourcePtrNull,  SignalSourcePtrNull,  SignalSourcePtrNull,  SignalSourcePtrNull,  SignalSourcePtrNull,  SignalSourcePtrNull}
{
}
Mixer::Mixer(SignalSourcePtr input0, SignalSourcePtr input1)
  : input_{input0, input1,  SignalSourcePtrNull,  SignalSourcePtrNull,  SignalSourcePtrNull,  SignalSourcePtrNull,  SignalSourcePtrNull,  SignalSourcePtrNull}
{
}
Mixer::Mixer(SignalSourcePtr input0, SignalSourcePtr input1, SignalSourcePtr input2)
  : input_{input0, input1, input2,  SignalSourcePtrNull,  SignalSourcePtrNull,  SignalSourcePtrNull,  SignalSourcePtrNull,  SignalSourcePtrNull}
{
}
Mixer::Mixer(SignalSourcePtr input0, SignalSourcePtr input1, SignalSourcePtr input2, SignalSourcePtr input3)
  : input_{input0, input1, input2, input3,  SignalSourcePtrNull,  SignalSourcePtrNull,  SignalSourcePtrNull,  SignalSourcePtrNull}
{
}
Mixer::Mixer(SignalSourcePtr input0, SignalSourcePtr input1, SignalSourcePtr input2, SignalSourcePtr input3,
             SignalSourcePtr input4)
  : input_{input0, input1, input2, input3, input4,  SignalSourcePtrNull,  SignalSourcePtrNull,  SignalSourcePtrNull}
{
}
Mixer::Mixer(SignalSourcePtr input0, SignalSourcePtr input1, SignalSourcePtr input2, SignalSourcePtr input3,
             SignalSourcePtr input4, SignalSourcePtr input5)
  : input_{input0, input1, input2, input3, input4, input5,  SignalSourcePtrNull,  SignalSourcePtrNull}
{          
}
Mixer::Mixer(SignalSourcePtr input0, SignalSourcePtr input1, SignalSourcePtr input2, SignalSourcePtr input3,
             SignalSourcePtr input4, SignalSourcePtr input5, SignalSourcePtr input6)
  : input_{input0, input1, input2, input3, input4, input5, input6,  SignalSourcePtrNull}
{
}
Mixer::Mixer(SignalSourcePtr input0, SignalSourcePtr input1, SignalSourcePtr input2, SignalSourcePtr input3,
             SignalSourcePtr input4, SignalSourcePtr input5, SignalSourcePtr input6, SignalSourcePtr input7)
  : input_{input0, input1, input2, input3, input4, input5, input6, input7}
{
}

void Mixer::SetChannelInput(uint8_t channel, SignalSourcePtr input)
{
  input_[channel] = input;
}

void Mixer::SetChannelGain(uint8_t channel, gain_t gain)
{
  gain_[channel] = gain;
}

void Mixer::Step(duration_t delta_t)
{
  /*
  for (uint8_t i = 0; i < kMaxChannels; ++i) {
    if (input_[i]) {
      input_[i]->Step(delta_t);
    }
  }
  */
}

voltage_t Mixer::Value()
{
  return static_cast<voltage_t>(
    (
      (input_[0] ? (static_cast<int32_t>(gain_[0]) * static_cast<int32_t>((input_[0])->Value())) : static_cast<int32_t>(0)) +
      (input_[1] ? (static_cast<int32_t>(gain_[1]) * static_cast<int32_t>((input_[1])->Value())) : static_cast<int32_t>(0)) +
      (input_[2] ? (static_cast<int32_t>(gain_[2]) * static_cast<int32_t>((input_[2])->Value())) : static_cast<int32_t>(0)) +
      (input_[3] ? (static_cast<int32_t>(gain_[3]) * static_cast<int32_t>((input_[3])->Value())) : static_cast<int32_t>(0)) +
      (input_[4] ? (static_cast<int32_t>(gain_[4]) * static_cast<int32_t>((input_[4])->Value())) : static_cast<int32_t>(0)) +
      (input_[5] ? (static_cast<int32_t>(gain_[5]) * static_cast<int32_t>((input_[5])->Value())) : static_cast<int32_t>(0)) +
      (input_[6] ? (static_cast<int32_t>(gain_[6]) * static_cast<int32_t>((input_[6])->Value())) : static_cast<int32_t>(0)) +
      (input_[7] ? (static_cast<int32_t>(gain_[7]) * static_cast<int32_t>((input_[7])->Value())) : static_cast<int32_t>(0))
    ) / static_cast<int32_t>(kGainUnity));
}

SignalSourcePtr Mixer::Output()
{
  return &output_;
}


void MixerSignalSource::Step(duration_t delta_t)
{
  mixer_->Step(delta_t);
}
voltage_t MixerSignalSource::Value()
{
  return mixer_->Value();
}

} // namespace synth
