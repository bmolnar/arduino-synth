#include "graph.h"

namespace synth {

GraphObjectBase::GraphObjectBase()
{
  Graph::Instance().Register(this);
}
GraphObjectBase::~GraphObjectBase()
{
  Graph::Instance().Unregister(this);
}




Graph::Graph()
 : head_{nullptr}, tail_{&head_}
{
}
void Graph::Register(GraphObjectBasePtr obj)
{
  obj->next_ = nullptr;
  obj->prev_ = tail_;
  (*tail_) = obj;
  tail_ = &obj->next_;
}
void Graph::Unregister(GraphObjectBasePtr obj)
{
  if (tail_ == &obj->next_) {
    tail_ = obj->prev_;
  }
  *obj->prev_ = obj->next_;
}
void Graph::Step(duration_t delta_t)
{
  for (GraphObjectBasePtr ptr = head_; ptr != nullptr; ptr = ptr->next_) {
    ptr->Step(delta_t);
  }
}
uint8_t Graph::ObjectCount()
{
  uint8_t result = 0;
  for (GraphObjectBasePtr ptr = head_; ptr != nullptr; ptr = ptr->next_) {
    result++;
  }
  return result;
}

//static Graph g_graph;

Graph& Graph::Instance()
{
  static Graph instance;
  return instance;
}

} // namespace synth
