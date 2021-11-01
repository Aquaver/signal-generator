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
  
  protected:
    virtual qreal signalFunction(qreal argument) override;
  
  private:
    qreal amplitude = 0;
    qreal constant = 0;
    qreal dutyCycle = 0;
    qreal period = 0;
    qreal phase = 0;
};

class Triangular : public Signal {
  public:
    Triangular() : amplitude{0}, constant{0}, deadTime{0}, edgeFalling{0}, edgeRising{0}, phase{0} {}
    Triangular(qreal amplitude, qreal constant, qreal deadTime, qreal edgeFalling, qreal edgeRising, qreal phase);
  
  protected:
    virtual qreal signalFunction(qreal argument) override;
  
  private:
    qreal amplitude = 0;
    qreal constant = 0;
    qreal deadTime = 0;
    qreal edgeFalling = 0;
    qreal edgeRising = 0;
    qreal phase = 0;
};
