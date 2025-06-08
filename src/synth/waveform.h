#ifndef SYNTH__WAVEFORM_H_
#define SYNTH__WAVEFORM_H_

#include "types.h"

namespace synth {

/**
 * Calculates value of a normalized sine waveform for a given phase
 *
 * @param phase The phase at which to evaluate the waveform
 * @return Value of the normalized waveform in [-kNormMax, kNormMax]
 */
norm_t WaveformSine(phase_t phase);

/**
 * Calculates value of a normalized triangle waveform for a given phase
 *
 * @param phase The phase at which to evaluate the waveform
 * @return Value of the normalized waveform in [-kNormMax, kNormMax]
 */
norm_t WaveformTriangle(phase_t phase);

/**
 * Calculates value of a normalized sawtooth waveform for a given phase
 *
 * @param phase The phase at which to evaluate the waveform
 * @return Value of the normalized waveform in [-kNormMax, kNormMax]
 */
norm_t WaveformSawtooth(phase_t phase);

/**
 * Calculates value of a normalized square waveform for a given phase
 *
 * @param phase The phase at which to evaluate the waveform
 * @return Value of the normalized waveform in [-kNormMax, kNormMax]
 */
norm_t WaveformSquare(phase_t phase);

/**
 * Calculates value of a normalized zero waveform for a given phase
 *
 * @param phase The phase at which to evaluate the waveform
 * @return Value of the normalized waveform in [-kNormMax, kNormMax]
 */
norm_t WaveformZero(phase_t phase);

} // namespace synth

#endif // SYNTH__WAVEFORM_H_
