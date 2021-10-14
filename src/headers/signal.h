#pragma once

#include <QtGlobal>
#include <QVector>

class Signal {
  public:
    bool isSelected = false;

    QVector<qreal> getArguments();
    QVector<qreal> getValues();

    void setArguments(QVector<qreal> newArguments);
    qint32 signalLength(); // Returns length of arguments/values set (they should be equal - if not then this function returns -1 which means an error).
  
  protected:
    static qreal shiftX, shiftY;

    QVector<qreal> arguments;
    QVector<qreal> values;

    virtual qreal signalFunction(qreal argument) = 0; // Master signal function (mathematical model) which converts an argument into proper value.
    virtual void calculateValues(); // Computes values vector from arguments vector.
  
  private:
    bool valuesValid = false;
    friend class CompoundSignal;
};
