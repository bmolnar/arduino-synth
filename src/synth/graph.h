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
  timestamp_t Timestamp();
  virtual void StepToPre(timestamp_t timestamp);
  virtual void StepToPost(timestamp_t timestamp);
  void StepTo(timestamp_t timestamp);

#if GRAPH_UTILS
  virtual uint8_t GetNumChildren();
  virtual GraphObjectBasePtr GetChild(uint8_t index);
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

/**
 * SignalSource
 */
class SignalSource
{
public:
  SignalSource(GraphObjectBase& owner, SignalGetterPtr getter);
  GraphObjectBase& Owner();
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
  SignalSink(GraphObjectBase& owner, voltage_t default_voltage = millivolts(0));
  SignalSink(GraphObjectBase& owner, SignalSourcePtr source, voltage_t default_voltage = millivolts(0));
  SignalSink(GraphObjectBase& owner, SignalSource& source, voltage_t default_voltage = millivolts(0));
  GraphObjectBase& Owner();
  SignalSourcePtr Source();
  bool Connected();
  void Connect(SignalSource& source);
  void Disconnect();
  voltage_t GetValue();
  voltage_t Value(const timestamp_t& timestamp);
protected:
  GraphObjectBase& owner_;
  SignalSourcePtr source_;
  voltage_t default_voltage_;
};
typedef SignalSink* SignalSinkPtr;


class SignalSinkStatic
{
public:
  SignalSinkStatic(GraphObjectBase& owner, SignalSource& source, voltage_t default_voltage = millivolts(0));
  GraphObjectBase& Owner();
  SignalSource& Source();
  bool Connected();
  void Connect(SignalSource& source);
  void Disconnect();
  voltage_t GetValue();
  voltage_t Value(const timestamp_t& timestamp);
protected:
  GraphObjectBase& owner_;
  SignalSource& source_;
  voltage_t default_voltage_;
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
