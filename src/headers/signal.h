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
};
