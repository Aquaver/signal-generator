#pragma once

#include "src/headers/signal.h"

class Sine : public Signal {
  public:
    Sine() : amplitude{0}, constant{0}, frequency{0}, phase{0} {}
    Sine(qreal amplitude, qreal constant, qreal frequency, qreal phase);
};
