#include "types.h"
#include "graph.h"

namespace synth {

voltage_t SignalSource::GetValue()
{
  return getter_->Get();
}
voltage_t SignalSource::Value(const timestamp_t& timestamp)
{
  owner_.StepTo(timestamp);
  return getter_->Get();
}



void SignalSink::Connect(SignalSource& source)
{
  if (source_ == &source) {
    return;
  }
  if (source_ != nullptr) {
    Disconnect();
  }
  source_ = &source;
}

void SignalSink::Disconnect()
{
  source_ = nullptr;
}

voltage_t SignalSink::GetValue()
{
  if (source_ != nullptr) {
    return source_->GetValue();
  } else {
    return 0;
  }
}
voltage_t SignalSink::Value(const timestamp_t& timestamp)
{
  if (source_ != nullptr) {
    return source_->Value(timestamp);
  } else {
    return 0;
  }
}

} // namespace synth
