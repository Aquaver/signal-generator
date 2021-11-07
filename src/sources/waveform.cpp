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

Triangular::Triangular(qreal amplitude, qreal constant, qreal deadTime, qreal edgeFalling, qreal edgeRising, qreal phase) : amplitude{amplitude}, constant{constant}, deadTime{deadTime}, edgeFalling{edgeFalling}, edgeRising{edgeRising}, phase{phase} {
  if (deadTime < 0) {
    perror("[Debug Error] Created Triangular waveform with negative dead time");
    this -> deadTime = 0;
  }

  if (edgeFalling <= 0) {
    perror("[Debug Error] Created Triangular waveform with non-positve falling edge length");
    this -> edgeFalling = 1;
  }

  if (edgeRising <= 0) {
    perror("[Debug Error] Created Triangular waveform with non-positive rising edge length");
    this -> edgeRising = 1;
  }
}

// Waveform signal functions implementations (overridden from base class).
qreal Sine::signalFunction(qreal argument) {
  return amplitude * sin(frequency * (argument - phase)) + constant;
}

qreal Square::signalFunction(qreal argument) {
  argument -= phase; // Waveform phase shift.

  qreal interval = floor(argument / period);
  qreal normalizedArgument = argument - (interval * period); // Argument narrowed (normalized) to interval.
  qreal dutyCycleBound = period * (dutyCycle / 100.0);

  if (dutyCycle > 0) {
    if (normalizedArgument <= dutyCycleBound) {
      return amplitude + constant;
    } else {
      return (-1 * amplitude) + constant;
    }
  } else {
    return (-1 * amplitude) + constant;
  }
}

qreal Triangular::signalFunction(qreal argument) {
  argument -= phase;

  qreal period = edgeRising + edgeFalling + deadTime;
  qreal interval = floor(argument / period);
  qreal normalizedArgument = argument - (interval * period);

  qreal falling = -1 * (amplitude / edgeFalling);
  qreal rising = amplitude / edgeRising;

  if (normalizedArgument <= edgeRising) {
    return normalizedArgument * rising + constant;
  } else if ((normalizedArgument > edgeRising) && (normalizedArgument <= (edgeRising + edgeFalling))) {
    return (normalizedArgument - edgeRising - edgeFalling) * falling + constant;
  } else {
    return constant; // Triangular waveform's dead time value.
  }
}
