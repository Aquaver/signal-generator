#include "src/headers/waveform.h"

// Waveform classes constructors.
Sine::Sine(qreal amplitude, qreal constant, qreal frequency, qreal phase) : amplitude{amplitude}, constant{constant}, frequency{frequency}, phase{phase} {
  // Sinusoidal waveform does not have any additional parameter value limits.
}
