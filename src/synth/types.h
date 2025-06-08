#ifndef SYNTH__TYPES_H_
#define SYNTH__TYPES_H_

#include <Arduino.h>

namespace synth {

//
// duration_t
//
typedef uint32_t duration_t;
static constexpr duration_t microseconds(uint32_t value)
{
  return static_cast<duration_t>(value);
}
static constexpr duration_t milliseconds(uint32_t value)
{
  return static_cast<duration_t>(1000 * value);
}
static constexpr duration_t seconds(uint32_t value)
{
  return static_cast<duration_t>(1000000 * value);
}

//
// timestamp_t
//
typedef uint32_t timestamp_t;

//
// duty_t
//
typedef uint8_t duty_t;
static const duty_t kDutyFull = 255;
static const duty_t kDutyHalf = 128;
static const duty_t kDutyQuarter = 64;
static const duty_t kDutyZero = 0;
static constexpr duty_t DutyPercent(uint8_t pct)
{
  return static_cast<duty_t>(static_cast<uint16_t>(pct) * 255 / 100);
}

//
// phase_t
//
// Represents values in [0, 2*pi) divided into 65536 increments
//
typedef uint16_t phase_t;
static constexpr phase_t kPhasePi = 32768;
static constexpr phase_t DurationToPhase(duration_t dur, duration_t period)
{
  return static_cast<phase_t>((static_cast<uint64_t>(dur) * static_cast<uint64_t>(kPhasePi) * 2 / static_cast<uint64_t>(period)) % (2 * static_cast<uint64_t>(kPhasePi)));
}

//
// unorm_t
//
// Represents unsigned values in [0, 65535/65536]
//
typedef uint16_t unorm_t;
static const unorm_t kUNormMin = 0;
static const unorm_t kUNormMax = 65535;

static const uint32_t UNORM_MIN = 0;
static const uint32_t UNORM_MAX = 65535;
static const uint32_t UNORM_DIVISOR = 65535;

//
// norm_t
//
// Represents signed values in [-32767/32767, 32767/32767]
//
typedef int16_t norm_t;
static const norm_t kNormMin = -32767;
static const norm_t kNormMax = 32767;

static const int32_t NORM_MIN = -32767;
static const int32_t NORM_MAX = 32767;
static const int32_t NORM_DIVISOR = 32767;

//
// voltage_t
//
// Represents voltage value in millivolts in range [-32.768 V, 32.767 V]
//
typedef int16_t voltage_t;
static const voltage_t kVoltageMin = -32768;
static const voltage_t kVoltageMax = 32767;
static constexpr voltage_t millivolts(int16_t value)
{
  return static_cast<voltage_t>(value);
}
static constexpr voltage_t volts(int16_t value)
{
  return static_cast<voltage_t>(1000 * value);
}

//
// gain_t
//
typedef int16_t gain_t;
static const gain_t kGainUnity = 4096;
static constexpr gain_t GainPercent(int16_t pct)
{
  return static_cast<gain_t>(static_cast<int32_t>(kGainUnity) * static_cast<int32_t>(pct) / 100);
}

//
// NormalizedPeriodicFunction
//
typedef norm_t (*NormalizedPeriodicFunction)(phase_t);
typedef NormalizedPeriodicFunction PeriodicFunction;
typedef NormalizedPeriodicFunction NormalizedWaveform;


//
// Template Helpers
//

// integral_constant
template<class T, T v>
struct integral_constant {
  static constexpr T value = v;
  using value_type = T;
  using type = integral_constant; // using injected-class-name
  constexpr operator value_type() const noexcept { return value; }
  constexpr value_type operator()() const noexcept { return value; } //since c++14
};

// bool types
typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

// is_same
template<class T, class U>
struct is_same : false_type {};
template<class T>
struct is_same<T, T> : true_type {};

// enable_if
template<bool B, class T = void>
struct enable_if {};
template<class T>
struct enable_if<true, T> { typedef T type; };
template<bool B, class T = void>
using enable_if_t = typename enable_if<B, T>::type;

} // namespace synth

#endif // SYNTH__TYPES_H_
