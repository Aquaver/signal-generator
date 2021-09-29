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

void Application::onAddSquare() {
  bool validAmplitude, validConstant, validDutyCycle, validPeriod, validPhase;

  qreal amplitude = ui -> textSquareParameterAmplitude -> text().toDouble(&validAmplitude);
  qreal constant = ui -> textSquareParameterConstant -> text().toDouble(&validConstant);
  qreal dutyCycle = ui -> textSquareParameterDutyCycle -> text().toDouble(&validDutyCycle);
  qreal period = ui -> textSquareParameterPeriod -> text().toDouble(&validPeriod);
  qreal phase = ui -> textSquareParameterPhase -> text().toDouble(&validPhase);

  if (validAmplitude == false || validConstant == false || validDutyCycle == false || validPeriod == false || validPhase == false) {
    errorAddingChart();
  } else if (dutyCycle < 0 || dutyCycle > 100) {
    errorInvalidDutyCycle();
  } else {
    QString identifier = QUuid::createUuid().toString(QUuid::StringFormat::WithoutBraces);
    Signal* newSignal = new Square(amplitude, constant, dutyCycle, period, phase);

    this -> chartList -> insert(identifier, newSignal);
    this -> groupList -> insert(identifier, ui -> chartField -> scene() -> createItemGroup({}));

    ui -> textSquareParameterAmplitude -> clear();
    ui -> textSquareParameterConstant -> clear();
    ui -> textSquareParameterDutyCycle -> clear();
    ui -> textSquareParameterPeriod -> clear();

    ui -> listCharts -> addItem(identifier);
    redrawAllCharts();
  }
}

void Application::onAddTriangular() {
  bool validAmplitude, validConstant, validDeadTime, validEdgeFalling, validEdgeRising, validPhase;

  qreal amplitude = ui -> textTriangularParameterAmplitude -> text().toDouble(&validAmplitude);
  qreal constant = ui -> textTriangularParameterConstant -> text().toDouble(&validConstant);
  qreal deadTime = ui -> textTriangularParameterDeadTime -> text().toDouble(&validDeadTime);
  qreal edgeFalling = ui -> textTriangularParameterEdgeFalling -> text().toDouble(&validEdgeFalling);
  qreal edgeRising = ui -> textTriangularParameterEdgeRising -> text().toDouble(&validEdgeRising);
  qreal phase = ui -> textTriangularParameterPhase -> text().toDouble(&validPhase);

  if (validAmplitude == false || validConstant == false || validDeadTime == false || validEdgeFalling == false || validEdgeRising == false || validPhase == false) {
    errorAddingChart();
  } else if (deadTime < 0) {
    errorInvalidDeadTime();
  } else if (edgeFalling <= 0 || edgeRising <= 0) {
    errorInvalidEdgeTime();
  } else {
    QString identifier = QUuid::createUuid().toString(QUuid::StringFormat::WithoutBraces);
    Signal* newSignal = new Triangular(amplitude, constant, deadTime, edgeFalling, edgeRising, phase);

    this -> chartList -> insert(identifier, newSignal);
    this -> groupList -> insert(identifier, ui -> chartField -> scene() -> createItemGroup({}));

    ui -> textTriangularParameterAmplitude -> clear();
    ui -> textTriangularParameterConstant -> clear();
    ui -> textTriangularParameterDeadTime -> clear();
    ui -> textTriangularParameterEdgeFalling -> clear();
    ui -> textTriangularParameterEdgeRising -> clear();
    ui -> textTriangularParameterPhase -> clear();

    ui -> listCharts -> addItem(identifier);
    redrawAllCharts();
  }
}

void Application::onShiftCenter() {
  chartShiftX = 0;
  chartShiftY = 0;

  updateCenterLabel();
  redrawAllCharts();
}

void Application::onShiftDown() {
  chartShiftY += gridUnitY;

  updateCenterLabel();
  redrawAllCharts();
}

void Application::onShiftLeft() {
  chartShiftX += gridUnitX;

  updateCenterLabel();
  redrawAllCharts();
}

void Application::onShiftRight() {
  chartShiftX -= gridUnitX;

  updateCenterLabel();
  redrawAllCharts();
}

void Application::onShiftUp() {
  chartShiftY -= gridUnitY;

  updateCenterLabel();
  redrawAllCharts();
}

void Application::onZoomIn() {
  gridUnitX /= 2;
  gridUnitY /= 2;

  redrawAllCharts();
  updateAxesLabel();
}

void Application::onZoomOut() {
  gridUnitX *= 2;
  gridUnitY *= 2;

  redrawAllCharts();
  updateAxesLabel();
}

void Application::onZoomReset() {
  gridUnitX = 1;
  gridUnitY = 1;

  redrawAllCharts();
  updateAxesLabel();
}

void Application::onRemove() { // Removes selected chart(s) from field.
  QList<QListWidgetItem*> deletedCharts = ui -> listCharts -> selectedItems();

  for (QListWidgetItem* chart : deletedCharts) {
    QString chartName = chart -> text();

    ui -> listCharts -> takeItem(ui -> listCharts -> row(chart));
    qDeleteAll(groupList -> value(chartName) -> childItems());

    chartList -> remove(chartName);
    groupList -> remove(chartName);
  }
}

void Application::onRename() { // Renames existing chart in list.
  QString newName = "";
  QString oldName = ui -> listCharts -> selectedItems().first() -> text();

  QInputDialog* nameInput = new QInputDialog(this);
  QString inputLabelLine1 = QString("Changing name of following chart: %1").arg(oldName);
  QString inputLabelLine2 = "Enter new name for this signal";

  nameInput -> setCancelButtonText("Cancel");
  nameInput -> setLabelText(inputLabelLine1 + '\n' + inputLabelLine2);
  nameInput -> setOkButtonText("Rename");
  nameInput -> setTextValue(oldName);
  nameInput -> setWindowTitle("Rename chart");

  if (nameInput -> exec() == QInputDialog::DialogCode::Accepted && nameInput -> textValue() != oldName && nameInput -> textValue().trimmed() != "") {
    newName = nameInput -> textValue();

    QList<QListWidgetItem*> oldCharts = ui -> listCharts -> findItems(oldName, Qt::MatchFlag::MatchExactly);
    QList<QListWidgetItem*> newCharts = ui -> listCharts -> findItems(newName, Qt::MatchFlag::MatchExactly);
    QListWidgetItem* oldChart = nullptr;
    QListWidgetItem* newChart = nullptr;

    if (oldCharts.isEmpty() == false) {
      oldChart = oldCharts.first();
    }

    if (newCharts.isEmpty() == false) {
      newChart = newCharts.first();
    }

    if (newChart != nullptr) {
      QMessageBox error;
      QString errorLine1 = "Chart with entered name already exists";
      QString errorLine2 = "Choose another one to rename";

      error.setIcon(QMessageBox::Icon::Critical);
      error.setText(errorLine1 + '\n' + errorLine2);
      error.setWindowTitle("Error");

      error.exec();
    } else {
      oldChart -> setText(newName);

      chartList -> insert(newName, chartList -> take(oldName));
      groupList -> insert(newName, groupList -> take(oldName));
    }
  }
}

// Interface menu events.
void Application::menuAdd() {
  createCompoundSignal(CompoundType::SUM, "SUM");
}

void Application::menuSubtract() {
  createCompoundSignal(CompoundType::DIFFERENCE, "DIFFERENCE");
}
