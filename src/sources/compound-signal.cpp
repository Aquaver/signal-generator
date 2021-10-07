#include "src/headers/compound-signal.h"

void CompoundSignal::setCompoundSignals(Signal *first, Signal *second) {
  firstSignal = first;
  secondSignal = second;
}

void CompoundSignal::setCompoundType(CompoundType newType) {
  type = newType;
}
