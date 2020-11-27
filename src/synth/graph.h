#ifndef SYNTH__GRAPH_H_
#define SYNTH__GRAPH_H_

#include "types.h"

namespace synth {

#define GRAPH_UTILS 1

class Graph;
typedef Graph* GraphPtr;

class GraphObjectBase;
typedef GraphObjectBase* GraphObjectBasePtr;

class GraphObjectBase
{
public:
  GraphObjectBase();
  virtual ~GraphObjectBase();

  virtual void StepPre(duration_t) {}
  virtual void StepPost(duration_t) {}
  void Step(duration_t delta_t);

  virtual void StepToPre(timestamp_t timestamp) {}
  virtual void StepToPost(timestamp_t timestamp) {}
  void StepTo(timestamp_t timestamp);

  timestamp_t Timestamp() { return timestamp_; }

#if GRAPH_UTILS
  virtual uint8_t GetNumChildren() { return 0; }
  virtual GraphObjectBasePtr GetChild(uint8_t index) { return nullptr; }
#endif

protected:
  timestamp_t timestamp_;
};

template <typename T>
class GraphObject : public GraphObjectBase
{
public:
  static T* FromBase(GraphObjectBasePtr base) { return static_cast<T*>(base); }
};


class Graph
{
public:
  static Graph& Instance();
  Graph();
protected:
  uint8_t count_{0};
};

class SignalGetter
{
public:
  virtual voltage_t Get() = 0;
};
typedef SignalGetter* SignalGetterPtr;


class SignalSource
{
public:
  SignalSource(GraphObjectBase& owner, SignalGetterPtr getter) : owner_(owner), getter_(getter) {}
  GraphObjectBase& Owner() { return owner_; }
  voltage_t GetValue();
  voltage_t Value(const timestamp_t& timestamp);
protected:
  GraphObjectBase& owner_;
  SignalGetterPtr getter_;
};

typedef SignalSource* SignalSourcePtr;

class SignalSink
{
public:
  SignalSink(GraphObjectBase& owner) : owner_(owner) {}
  SignalSink(GraphObjectBase& owner, SignalSourcePtr source) : owner_(owner), source_(source) {}
  GraphObjectBase& Owner() { return owner_; }
  SignalSourcePtr Source() { return source_; }
  bool Connected() { return (source_ != nullptr); }
  void Connect(SignalSource& source);
  void Disconnect();
  voltage_t GetValue();
  voltage_t Value(const timestamp_t& timestamp);
protected:
  GraphObjectBase& owner_;
  SignalSourcePtr source_;
};


class Connection
{
public:
  Connection(SignalSource& source, SignalSink& sink);
  ~Connection();
protected:
  SignalSource& source_;
  SignalSink& sink_;
};


} // namespace synth

#endif // SYNTH__GRAPH_H_
