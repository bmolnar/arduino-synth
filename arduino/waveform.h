#ifndef SYNTH__PERIODIC_FUNCTION_H_
#define SYNTH__PERIODIC_FUNCTION_H_

#include "types.h"

namespace synth {

norm_t WaveformSine(phase_t phase);
norm_t WaveformTriangle(phase_t phase);
norm_t WaveformSawtooth(phase_t phase);
norm_t WaveformSquare(phase_t phase);
norm_t WaveformZero(phase_t phase);

} // namespace synth

#endif // SYNTH__PERIODIC_FUNCTION_H_
