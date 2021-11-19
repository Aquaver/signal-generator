# Signal Generator

Signal Generator is a project of a GUI application based on Qt framework, which allows generating signal models that are representations of periodic waveforms (for instance electrical ones) in four main ways - as sinusoidal, square, triangular and sawtooth waveform. This program uses a simple class hierarchy consisting of an abstract base class which defines mathematical model of a signal, and three subclasses implementing sine, square and triangular (including sawtooth) waveforms. In addition, a class which comes from part of project that was generated by Qt, used to handle graphical user interface, realizes `use` relation between itself and these classes when generating waveforms, to transform the mathematical model into graphical representation of the signal.

## Class structure implementation

Application's main logic part consists of header files with field and method definitions, and specific for this language - separate source files with implementation of that class methods (including mathematical model functions) for generated waveforms.

```cpp
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
```

The first class, which is the base abstract one for all types of waveforms is named `Signal` and its body is implemented in its own file. It consists of fields that define behavior of each possible generated signal and simple operations that can be performed on them, such as setting a set of arguments, computing values and retrieving that set of calculated values for this waveform. In addition, a `friend` relationship with another class `CompoundSignal` is also defined here, to allow access to private fields of this class and implement creating compound waveforms.

Second class, but first derived from `Signal` one is named `Sine` which indicates that it defines the mathematical model of sinusoidal waveform. As it inherits from a common base class, it is not needed to redefine all the methods and fields. However, in order to be able to create instances of this class, it must overload and implement `signalFunction()` method in which the actual model of the waveform will be stored. This function allows computing set of arguments into set of values. Besides, this class contains some necessary parameters of sine wave - amplitude, frequency, phase shift (horizontal shift) and constant component (vertical shift). Example of generated sinusoidal waveform is shown on the picture below.

<p align="center">
  <img alt="Sine waveform example" src="https://raw.githubusercontent.com/Aquaver/signal-generator/master/assets/example-sine.png">
</p>

The header code file of the next class does not differ from the code of the previous one. Class `Square` defines parameters of the square (rectangular) waveform. It implements its own way of computing function value by overriding `signalFunction()` method and allows creating a new instance of the waveform through the constructor. However, there is one parameter that is limited to strict range. This parameter is defined as `dutyCycle` and its value must be in range from 0 up to 100 (inclusive), so when creating new object, there must be some validation mechanism for checking this condition. For this purpose, an additional implementation file was created, in which the constructor body was included.

```cpp
Square::Square(qreal amplitude, qreal constant, qreal dutyCycle, qreal period, qreal phase) : amplitude{amplitude}, constant{constant}, dutyCycle{dutyCycle}, period{period}, phase{phase} {
  if (dutyCycle < 0 || dutyCycle > 100) {
    perror("[Debug Error] Created Square waveform with invalid duty cycle");
    dutyCycle = 50;
  }
}
```
