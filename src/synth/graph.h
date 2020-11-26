#ifndef SYNTH__GRAPH_H_
#define SYNTH__GRAPH_H_

#include "types.h"

namespace synth {

class Graph;
typedef Graph* GraphPtr;

class GraphObjectBase;
typedef GraphObjectBase* GraphObjectBasePtr;



class GraphObjectBase
{
public:
  GraphObjectBase();
  virtual ~GraphObjectBase();
  virtual void Step(duration_t delta_t) = 0;
protected:
  GraphObjectBasePtr next_{nullptr};
  GraphObjectBasePtr* prev_{nullptr};
  friend class Graph;
};

template <typename T>
class GraphObject : public GraphObjectBase
{
public:
  static T* FromBase(GraphObjectBasePtr base) { return static_cast<T*>(base); }
  virtual void Step(duration_t delta_t) = 0;
};

class Graph
{
public:
  static Graph& Instance();

  Graph();
  void Step(duration_t delta_t);
  void Register(GraphObjectBasePtr obj);
  void Unregister(GraphObjectBasePtr obj);
  uint8_t ObjectCount();

protected:
  GraphObjectBasePtr head_{nullptr};
  GraphObjectBasePtr* tail_{&head_};
  uint8_t count_{0};
};


} // namespace synth

#endif // SYNTH__GRAPH_H_
