#pragma once

#include "src/headers/compound-type.h"
#include "src/headers/signal.h"

class CompoundSignal : public Signal {
  public:
    void setCompoundSignals(Signal* first, Signal* second);
    void setCompoundType(CompoundType newType);
  
  protected:
    virtual qreal signalFunction(qreal argument) override;
  
  private:
    CompoundType type = CompoundType::SUM; // Sum is the default signal compound type.
    Signal* firstSignal = nullptr;
    Signal* secondSignal = nullptr;
};
