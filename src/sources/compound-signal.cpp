#include "src/headers/compound-signal.h"

void CompoundSignal::setCompoundSignals(Signal *first, Signal *second) {
  firstSignal = first;
  secondSignal = second;
}
