#include "src/headers/application.h"
#include "src/headers/waveform.h"
#include "ui_application.h"

#include <QAction>
#include <QInputDialog>
#include <QMessageBox>
#include <QUuid>

// Connecting all events functions below to GUI buttons.
void Application::initSlots() {
  connect(ui -> buttonAddSine, SIGNAL(clicked()), this, SLOT(onAddSine()));
  connect(ui -> buttonAddSquare, SIGNAL(clicked()), this, SLOT(onAddSquare()));
  connect(ui -> buttonAddTriangular, SIGNAL(clicked()), this, SLOT(onAddTriangular()));

  connect(ui -> buttonMoveCenter, SIGNAL(clicked()), this, SLOT(onShiftCenter()));
  connect(ui -> buttonMoveDown, SIGNAL(clicked()), this, SLOT(onShiftDown()));
  connect(ui -> buttonMoveLeft, SIGNAL(clicked()), this, SLOT(onShiftLeft()));
  connect(ui -> buttonMoveRight, SIGNAL(clicked()), this, SLOT(onShiftRight()));
  connect(ui -> buttonMoveUp, SIGNAL(clicked()), this, SLOT(onShiftUp()));

  connect(ui -> buttonViewZoomIn, SIGNAL(clicked()), this, SLOT(onZoomIn()));
  connect(ui -> buttonViewZoomOut, SIGNAL(clicked()), this, SLOT(onZoomOut()));
  connect(ui -> buttonViewZoomReset, SIGNAL(clicked()), this, SLOT(onZoomReset()));

  connect(ui -> buttonMenuDelete, SIGNAL(clicked()), this, SLOT(onRemove()));
  connect(ui -> buttonMenuRename, SIGNAL(clicked()), this, SLOT(onRename()));

  connect(ui -> listCharts, SIGNAL(itemSelectionChanged()), this, SLOT(onItemSelected()));
}

// Interface buttons events.
void Application::onAddSine() {
  bool validAmplitude, validConstant, validFrequency, validPhase;

  qreal amplitude = ui -> textSineParameterAmplitude -> text().toDouble(&validAmplitude);
  qreal constant = ui -> textSineParameterConstant -> text().toDouble(&validConstant);
  qreal frequency = ui -> textSineParameterFrequency -> text().toDouble(&validFrequency);
  qreal phase = ui -> textSineParameterPhase -> text().toDouble(&validPhase);

  if (validAmplitude == false || validConstant == false || validFrequency == false || validPhase == false) {
    errorAddingChart();
  } else {
    QString identifier = QUuid::createUuid().toString(QUuid::StringFormat::WithoutBraces);
    Signal* newSignal = new Sine(amplitude, constant, frequency, phase);

    this -> chartList -> insert(identifier, newSignal);
    this -> groupList -> insert(identifier, ui -> chartField -> scene() -> createItemGroup({}));

    ui -> textSineParameterAmplitude -> clear();
    ui -> textSineParameterConstant -> clear();
    ui -> textSineParameterFrequency -> clear();
    ui -> textSineParameterPhase -> clear();

    ui -> listCharts -> addItem(identifier);
    redrawAllCharts();
  }
}
