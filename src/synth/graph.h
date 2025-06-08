#ifndef SYNTH__GRAPH_H_
#define SYNTH__GRAPH_H_

#include "types.h"

namespace synth {

#define GRAPH_UTILS 1

//
// Forward declarations
//
class Graph;
typedef Graph* GraphPtr;

class GraphObjectBase;
typedef GraphObjectBase* GraphObjectBasePtr;

class SignalGetter;
typedef SignalGetter* SignalGetterPtr;

class SignalSource;
typedef SignalSource* SignalSourcePtr;

class SignalSink;
typedef SignalSink* SignalSinkPtr;



/**
 * Graph
 *
 * Class that holds the run graph of a system of components
 */
class Graph
{
public:

  /**
   * Initializes a Graph object
   */
  Graph();

  /**
   * Returns singleton instance of Graph object
   *
   * @return A singleton instance of Graph object
   */
  static Graph& Instance();

protected:
  uint8_t count_{0};
};


/**
 * GraphObjectBase
 *
 * Base class all graph objects
 */
class GraphObjectBase
{
public:

  /**
   * Initializes graph object
   */
  GraphObjectBase();

  /**
   * Virtual deconstructor
   */
  virtual ~GraphObjectBase();

  /**
   * Gets the object's most recent timestamp
   *
   * @return Current timestamp of object
   */
  timestamp_t Timestamp();

  /**
   * Update graph object to given timestamp
   *
   * During this call, components do internal processing to retrieve signals
   * from their inputs, update their internal state and make signals available
   * at their outputs
   *
   * @param timestamp The timestamp to update to
   */
  void StepTo(timestamp_t timestamp);

  /**
   * Called by run graph just before StepTo
   *
   * Can be overwritten by derived classes
   *
   * @param timestamp The time stamp provided in the StepTo call
   */
  virtual void StepToPre(timestamp_t timestamp);

  /**
   * Called by run graph just after StepTo
   *
   * Can be overwritten by derived classes
   *
   * @param timestamp The time stamp provided in the StepTo call
   */
  virtual void StepToPost(timestamp_t timestamp);

#if GRAPH_UTILS
  virtual uint8_t GetNumChildren();
  virtual GraphObjectBasePtr GetChild(uint8_t index);
#endif // GRAPH_UTILS

protected:
  timestamp_t timestamp_;
};



/**
 * GraphObject
 *
 * A templatized base class for all graph objects
 */
template <typename T>
class GraphObject : public GraphObjectBase
{
public:

  /**
   * Cast a GraphObject object into a derived class
   *
   * @param base A pointer to an object of class GraphObjectBase
   * @return A pointer to an object of class T
   */
  static T* FromBase(GraphObjectBasePtr base) { return static_cast<T*>(base); }
};


/**
 * SignalGetter
 *
 * Base class for providing a voltage signal. It has one method, Get, which
 * must be implemented by its subclasses.
 */
class SignalGetter
{
public:

  /**
   * Gets the current value of the signal, in Volts
   */
  virtual voltage_t Get() = 0;
};


/**
 * SignalSource
 *
 * A class that identifies a signal source belonging to a graph object
 */
class SignalSource
{
public:
  /**
   * Initializes a SignalSource instance with a given owner and a
   * SignalGetter
   *
   * @param owner Reference to the graph object owning this SignalSource
   * @param getter A pointer to a SignalGetter object
   */
  SignalSource(GraphObjectBase& owner, SignalGetterPtr getter);

  /**
   * Gets the owning graph object of this signal source
   *
   * @return A reference to the GraphObjectBase object of the owner
   */
  GraphObjectBase& Owner();

  /**
   * Gets the current value of the output signal
   *
   * @return The current value of the output signal, in Volts
   */
  voltage_t GetValue();

  /**
   * Gets the value of the output signal after updating the owning graph object
   * to the given timestamp
   *
   * @param The timestamp to update the owning graph object to
   * @return The current value of the output signal, in Volts
   */
  voltage_t Value(const timestamp_t& timestamp);

protected:
  GraphObjectBase& owner_;
  SignalGetterPtr getter_;
};



/**
 * SignalSink
 *
 * A class that identifies a consumer of signals. When connected to a
 * SignalSource, this represents a connection where signal data is
 * automatically sent from the SignalSource to the SignalSink whenever the
 * components are updated.
 */
class SignalSink
{
public:

  /**
   * Initializes a SignalSink with a given owner and default signal voltage
   *
   * @param owner Reference to the graph object owning this SignalSink
   * @param default_voltage The default value of the signal input before any
   *                        data arrives
   */
  SignalSink(GraphObjectBase& owner, voltage_t default_voltage = millivolts(0));

  /**
   * Initializes a SignalSink with a given owner and default signal voltage
   * and connects to a given SignalSource
   *
   * @param owner Reference to the graph object owning this SignalSink
   * @param source A pointer to the SignalSource object to connect to
   * @param default_voltage The default value of the signal input before any
   *                        data arrives
   */
  SignalSink(GraphObjectBase& owner, SignalSourcePtr source, voltage_t default_voltage = millivolts(0));

  /**
   * Initializes a SignalSink with a given owner and default signal voltage
   * and connects to a given SignalSource
   *
   * @param owner Reference to the graph object owning this SignalSink
   * @param source A reference to the SignalSource object to connect to
   * @param default_voltage The default value of the signal input before any
   *                        data arrives
   */
  SignalSink(GraphObjectBase& owner, SignalSource& source, voltage_t default_voltage = millivolts(0));

  /**
   * Gets the owning graph object
   *
   * @return A reference to the GraphObjectBase object of the owner
   */
  GraphObjectBase& Owner();

  /**
   * Gets the a pointer to the SignalSource object this SignalSink is
   * connected to
   *
   * @return A pointer to the SignalSource object if connected, otherwise nullptr
   */
  SignalSourcePtr Source();

  /**
   * Checks if connected
   *
   * @return true if connected, else false
   */
  bool Connected();

  /**
   * Connects this SignalSink to a SignalSource object
   *
   * @param A reference to the SignalSource object to connect to
   */
  void Connect(SignalSource& source);

  /**
   * Disconnects this SignalSink from any SignalSource object, if connected
   */
  void Disconnect();

  /**
   * If connected to a SignalSource, gets the current value of its output. If
   * not connected, returns default_voltage.
   *
   * @return The current value (in Volts) of the output of the connected
   *         SignalSource, or default_voltage if not connected
   */
  voltage_t GetValue();

  /**
   * If connected to a SignalSource, gets the current value of its output after
   * updating its owning graph object to the given timestamp. If not connected,
   * return default_voltage.
   *
   * @param The timestamp to update the peer's owning graph object to
   * @return The current value (in Volts) of the output of the connected
   *         SignalSource, or default_voltage if not connected
   */
  voltage_t Value(const timestamp_t& timestamp);

protected:
  GraphObjectBase& owner_;
  SignalSourcePtr source_;
  voltage_t default_voltage_;
};



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


/**
 * Connection
 *
 * Establishes a connection between a given SignalSource and a SignalSink
 *
 * The SignalSource and SignalSink will remain connected for the lifetime of
 * this object
 */
class Connection
{
public:

  /**
   * Initializes a connection between the given SignalSource and SignalSink
   *
   * @param source A reference to a SignalSource object
   * @param sink A reference to a SignalSink object
   */
  Connection(SignalSource& source, SignalSink& sink);

  /**
   * Destructs connection object
   *
   * Upon destruction, this will disconnect the SignalSource and SignalSink
   */
  ~Connection();

protected:
  SignalSource& source_;
  SignalSink& sink_;
};


} // namespace synth

#endif // SYNTH__GRAPH_H_
