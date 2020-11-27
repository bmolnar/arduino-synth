#ifndef SYNTH__TYPES_H_
#define SYNTH__TYPES_H_

#include <Arduino.h>

namespace synth {

// Duration
typedef uint32_t duration_t;
static inline duration_t microseconds(uint32_t value)
{
  return static_cast<duration_t>(value);
}
static inline duration_t milliseconds(uint32_t value)
{
  return static_cast<duration_t>(1000 * value);
}
static inline duration_t seconds(uint32_t value)
{
  return static_cast<duration_t>(1000000 * value);
}

typedef duration_t timestamp_t;


// Duty
typedef uint8_t duty_t;
static const duty_t kDutyFull = 255;
static const duty_t kDutyHalf = 128;
static const duty_t kDutyQuarter = 64;
static const duty_t kDutyZero = 0;
static inline duty_t DutyPercent(uint8_t pct)
{
  return static_cast<duty_t>(static_cast<uint16_t>(pct) * 255 / 100);
}

// Phase
typedef uint16_t phase_t;
static const phase_t kPhasePi = 32768;

// Unsigned Normalized Value [0, 65535/65536]
typedef uint16_t unorm_t;
static const uint32_t UNORM_MIN = 0;
static const uint32_t UNORM_MAX = 65535;
static const uint32_t UNORM_DIVISOR = 65535;

// Signed Normalized Value [-32768/32768, 32767/32768]
typedef int16_t norm_t;
static const int32_t NORM_MIN = -32767;
static const int32_t NORM_MAX = 32767;
static const int32_t NORM_DIVISOR = 32767;

// Voltage
typedef int16_t voltage_t;
static inline voltage_t millivolts(int16_t value)
{
  return static_cast<voltage_t>(value);
}
static inline voltage_t volts(int16_t value)
{
  return static_cast<voltage_t>(1000 * value);
}
static const voltage_t kVoltageMin = -32768;
static const voltage_t kVoltageMax = 32767;


// Gain
typedef int16_t gain_t;
static const gain_t kGainUnity = 4096;


// Function
typedef norm_t (*NormalizedPeriodicFunction)(phase_t);
typedef NormalizedPeriodicFunction PeriodicFunction;
typedef NormalizedPeriodicFunction NormalizedWaveform;


} // namespace synth

#endif // SYNTH__TYPES_H_
