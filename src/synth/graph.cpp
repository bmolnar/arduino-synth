#include "graph.h"

namespace synth {

//
// GraphObjectBase
//
GraphObjectBase::GraphObjectBase()
{
}
GraphObjectBase::~GraphObjectBase()
{
}
timestamp_t GraphObjectBase::Timestamp()
{
  return timestamp_;
}
void GraphObjectBase::StepToPre(timestamp_t timestamp)
{
  ((void) timestamp);
}
void GraphObjectBase::StepToPost(timestamp_t timestamp)
{
  ((void) timestamp);
}
void GraphObjectBase::StepTo(timestamp_t timestamp)
{
  StepToPre(timestamp);
  timestamp_ = timestamp;
  StepToPost(timestamp);
}

#if GRAPH_UTILS
uint8_t GraphObjectBase::GetNumChildren()
{
  return 0;
}
GraphObjectBasePtr GraphObjectBase::GetChild(uint8_t index)
{
  ((void) index);
  return nullptr;
}
#endif // GRAPH_UTILS



//
// Graph
//
Graph::Graph()
{
}
Graph& Graph::Instance()
{
  static Graph instance;
  return instance;
}



//
// SignalSource
//
SignalSource::SignalSource(GraphObjectBase& owner, SignalGetterPtr getter)
  : owner_(owner), getter_(getter)
{
}
GraphObjectBase& SignalSource::Owner()
{
  return owner_;
}
voltage_t SignalSource::GetValue()
{
  return getter_->Get();
}
voltage_t SignalSource::Value(const timestamp_t& timestamp)
{
  while (owner_.Timestamp() < timestamp) {
    owner_.StepTo(timestamp);
  }
  return GetValue();
}



// SignalSink
SignalSink::SignalSink(GraphObjectBase& owner, voltage_t default_voltage)
  : owner_(owner), source_(nullptr), default_voltage_(default_voltage)
{
}
SignalSink::SignalSink(GraphObjectBase& owner, SignalSourcePtr source, voltage_t default_voltage)
  : owner_(owner), source_(source), default_voltage_(default_voltage)
{
}
SignalSink::SignalSink(GraphObjectBase& owner, SignalSource& source, voltage_t default_voltage)
  : owner_(owner), source_(&source), default_voltage_(default_voltage)
{
}
GraphObjectBase& SignalSink::Owner()
{
  return owner_;
}
SignalSourcePtr SignalSink::Source()
{
  return source_;
}
bool SignalSink::Connected()
{
  return (source_ != nullptr);
}
void SignalSink::Connect(SignalSource& source)
{
  source_ = &source;
}
void SignalSink::Disconnect()
{
  source_ = nullptr;
}
voltage_t SignalSink::GetValue()
{
  return Connected() ? source_->GetValue() : default_voltage_;
}
voltage_t SignalSink::Value(const timestamp_t& timestamp)
{
  return Connected() ? source_->Value(timestamp) : default_voltage_;
}


//
// Connection
//
Connection::Connection(SignalSource& source, SignalSink& sink)
    : source_(source), sink_(sink)
{
  sink_.Connect(source_);
}
Connection::~Connection()
{
  sink_.Disconnect();
}


} // namespace synth
