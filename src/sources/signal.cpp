#include "src/headers/signal.h"

qreal Signal::shiftX = 1;
qreal Signal::shiftY = 1;

void Signal::calculateValues() {
  values.clear();

  for (qreal argument : arguments) {
    values.append(signalFunction(argument)); // Calculating raw signal function values without transforming them into chart position (in pixels).
  }
}

QVector<qreal> Signal::getArguments() {
  return arguments;
}

QVector<qreal> Signal::getValues() {
  if (valuesValid == false) {
    calculateValues();
    valuesValid = true;
  }

  return values;
}

void Signal::setArguments(QVector<qreal> newArguments) {
  arguments = newArguments;
  valuesValid = false;
}
