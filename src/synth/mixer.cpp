#include "mixer.h"

namespace synth {

Mixer::Mixer()
{
}
Mixer::Mixer(SignalSource& input0)
{
  input_[0].Connect(input0);
}
Mixer::Mixer(SignalSource& input0, SignalSource& input1)
{
  input_[0].Connect(input0);
  input_[1].Connect(input1);
}
Mixer::Mixer(SignalSource& input0, SignalSource& input1, SignalSource& input2)
{
  input_[0].Connect(input0);
  input_[1].Connect(input1);
  input_[2].Connect(input2);
}
Mixer::Mixer(SignalSource& input0, SignalSource& input1, SignalSource& input2, SignalSource& input3)
{
  input_[0].Connect(input0);
  input_[1].Connect(input1);
  input_[2].Connect(input2);
  input_[3].Connect(input3);
}
Mixer::Mixer(SignalSource& input0, SignalSource& input1, SignalSource& input2, SignalSource& input3,
             SignalSource& input4)
{
  input_[0].Connect(input0);
  input_[1].Connect(input1);
  input_[2].Connect(input2);
  input_[3].Connect(input3);
  input_[4].Connect(input4);
}
Mixer::Mixer(SignalSource& input0, SignalSource& input1, SignalSource& input2, SignalSource& input3,
             SignalSource& input4, SignalSource& input5)
{
  input_[0].Connect(input0);
  input_[1].Connect(input1);
  input_[2].Connect(input2);
  input_[3].Connect(input3);
  input_[4].Connect(input4);
  input_[5].Connect(input5);
}
Mixer::Mixer(SignalSource& input0, SignalSource& input1, SignalSource& input2, SignalSource& input3,
             SignalSource& input4, SignalSource& input5, SignalSource& input6)
{
  input_[0].Connect(input0);
  input_[1].Connect(input1);
  input_[2].Connect(input2);
  input_[3].Connect(input3);
  input_[4].Connect(input4);
  input_[5].Connect(input5);
  input_[6].Connect(input6);
}
Mixer::Mixer(SignalSource& input0, SignalSource& input1, SignalSource& input2, SignalSource& input3,
             SignalSource& input4, SignalSource& input5, SignalSource& input6, SignalSource& input7)
{
  input_[0].Connect(input0);
  input_[1].Connect(input1);
  input_[2].Connect(input2);
  input_[3].Connect(input3);
  input_[4].Connect(input4);
  input_[5].Connect(input5);
  input_[6].Connect(input6);
  input_[7].Connect(input7);
}

#if GRAPH_UTILS
uint8_t Mixer::GetNumChildren()
{
  uint8_t result = 0;
  for (uint8_t i = 0; i < kMaxChannels; ++i) {
    if (input_[i].Connected()) {
      result++;
    }
  }
  return result;
}
GraphObjectBasePtr Mixer::GetChild(uint8_t index)
{
  return &input_[index].Source()->Owner();
}
#endif // GRAPH_UTILS

void Mixer::SetChannelInput(uint8_t channel, SignalSource& input)
{
  input_[channel].Connect(input);
}

void Mixer::SetChannelGain(uint8_t channel, gain_t gain)
{
  gain_[channel] = gain;
}



void Mixer::StepPre(duration_t delta_t)
{
  for (uint8_t i = 0; i < kMaxChannels; ++i) {
    if (input_[i].Connected()) {
      input_[i].Source()->Owner().Step(delta_t);
    }
  }
}
void Mixer::StepPost(duration_t delta_t)
{
  ((void) delta_t);
}




void Mixer::StepToPre(timestamp_t timestamp)
{
  for (uint8_t i = 0; i < kMaxChannels; ++i) {
    if (input_[i].Connected()) {
      input_[i].Source()->Owner().StepTo(timestamp);
    }
  }
}
void Mixer::StepToPost(timestamp_t timestamp)
{
  ((void) timestamp);
}



voltage_t Mixer::Value()
{
  return static_cast<voltage_t>(
    (
      (input_[0].Connected() ? (static_cast<int32_t>(gain_[0]) * static_cast<int32_t>(input_[0].GetValue())) : static_cast<int32_t>(0)) +
      (input_[1].Connected() ? (static_cast<int32_t>(gain_[1]) * static_cast<int32_t>(input_[1].GetValue())) : static_cast<int32_t>(0)) +
      (input_[2].Connected() ? (static_cast<int32_t>(gain_[2]) * static_cast<int32_t>(input_[2].GetValue())) : static_cast<int32_t>(0)) +
      (input_[3].Connected() ? (static_cast<int32_t>(gain_[3]) * static_cast<int32_t>(input_[3].GetValue())) : static_cast<int32_t>(0)) +
      (input_[4].Connected() ? (static_cast<int32_t>(gain_[4]) * static_cast<int32_t>(input_[4].GetValue())) : static_cast<int32_t>(0)) +
      (input_[5].Connected() ? (static_cast<int32_t>(gain_[5]) * static_cast<int32_t>(input_[5].GetValue())) : static_cast<int32_t>(0)) +
      (input_[6].Connected() ? (static_cast<int32_t>(gain_[6]) * static_cast<int32_t>(input_[6].GetValue())) : static_cast<int32_t>(0)) +
      (input_[7].Connected() ? (static_cast<int32_t>(gain_[7]) * static_cast<int32_t>(input_[7].GetValue())) : static_cast<int32_t>(0))
    ) / static_cast<int32_t>(kGainUnity));
}
SignalSource& Mixer::Output()
{
  return output_;
}

voltage_t MixerValueGetter::Get()
{
  return mixer_->Value();
}

} // namespace synth
