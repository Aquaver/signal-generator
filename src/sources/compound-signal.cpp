#include "src/headers/compound-signal.h"

void CompoundSignal::setCompoundSignals(Signal *first, Signal *second) {
  firstSignal = first;
  secondSignal = second;
}

void CompoundSignal::setCompoundType(CompoundType newType) {
  type = newType;
}

qreal CompoundSignal::signalFunction(qreal argument) {
  if (firstSignal != nullptr && secondSignal != nullptr) {
    if (type == CompoundType::SUM) {
      return firstSignal -> signalFunction(argument) + secondSignal -> signalFunction(argument);
    } else if (type == CompoundType::DIFFERENCE) {
      return firstSignal -> signalFunction(argument) - secondSignal -> signalFunction(argument);
    } else {
      perror("[Debug Error] Invalid compound type");
      return -1;
    }
  } else {
    perror("[Debug Error] One of signals has not been initialized (or both of them)");
    return -1;
  }
}
