#pragma once

#include "src/headers/signal.h"

class Sine : public Signal {
  public:
    Sine() : amplitude{0}, constant{0}, frequency{0}, phase{0} {}
    Sine(qreal amplitude, qreal constant, qreal frequency, qreal phase);
  
  protected:
    virtual qreal signalFunction(qreal argument) override;
  
  private:
    qreal amplitude = 0;
    qreal constant = 0;
    qreal frequency = 0;
    qreal phase = 0;
};

class Square : public Signal {
  public:
    Square() : amplitude{0}, constant{0}, dutyCycle{0}, period{0}, phase{0} {}
    Square(qreal amplitude, qreal constant, qreal dutyCycle, qreal period, qreal phase);
};
