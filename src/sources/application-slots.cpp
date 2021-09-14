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
