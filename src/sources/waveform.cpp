#include "src/headers/waveform.h"

// Waveform classes constructors.
Sine::Sine(qreal amplitude, qreal constant, qreal frequency, qreal phase) : amplitude{amplitude}, constant{constant}, frequency{frequency}, phase{phase} {
  // Sinusoidal waveform does not have any additional parameter value limits.
}

Square::Square(qreal amplitude, qreal constant, qreal dutyCycle, qreal period, qreal phase) : amplitude{amplitude}, constant{constant}, dutyCycle{dutyCycle}, period{period}, phase{phase} {
  if (dutyCycle < 0 || dutyCycle > 100) {
    perror("[Debug Error] Created Square waveform with invalid duty cycle");
    dutyCycle = 50;
  }
}
