#include "graph.h"

namespace synth {

GraphObjectBase::GraphObjectBase()
{
}
GraphObjectBase::~GraphObjectBase()
{
}

void GraphObjectBase::Step(duration_t delta_t)
{
  StepPre(delta_t);
  timestamp_ += delta_t;
  StepPost(delta_t);
}
void GraphObjectBase::StepTo(timestamp_t timestamp)
{
  StepToPre(timestamp);
  timestamp_ = timestamp;
  StepToPost(timestamp);
}

Graph::Graph()
{
}
Graph& Graph::Instance()
{
  static Graph instance;
  return instance;
}


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
