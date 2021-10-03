#pragma once

#include "src/headers/compound-type.h"
#include "src/headers/signal.h"

class CompoundSignal : public Signal {
  public:
    void setCompoundSignals(Signal* first, Signal* second);
    void setCompoundType(CompoundType newType);
};
