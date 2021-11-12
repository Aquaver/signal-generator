QT += core gui widgets
CONFIG += c++11
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
  src/sources/application.cpp \
  src/sources/application-errors.cpp \
  src/sources/application-initialize.cpp \
  src/sources/application-menu.cpp \
  src/sources/application-slots.cpp \
  src/sources/compound-signal.cpp \
  src/sources/main.cpp \
  src/sources/signal.cpp \
  src/sources/waveform.cpp

HEADERS += \
  src/headers/application.h \
  src/headers/compound-signal.h \
  src/headers/compound-type.h \
  src/headers/signal.h \
  src/headers/waveform.h

FORMS += \
  forms/application.ui
