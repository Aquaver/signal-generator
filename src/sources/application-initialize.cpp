#include "src/headers/application.h"
#include "ui_application.h"

#include <QGraphicsScene>
#include <QMenu>
#include <QPen>

void Application::initChartField() {
  ui -> chartField -> setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff); // Disabling unnecessary scroll bars.
  ui -> chartField -> setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);

  ui -> chartAxisX -> setStyleSheet("color: " + axesColor.name() + ';');
  ui -> chartAxisY -> setStyleSheet("color: " + axesColor.name() + ';');

  ui -> listCharts -> setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);

  if (ui -> chartField -> scene() == nullptr) {
    ui -> chartField -> setScene(new QGraphicsScene(0, 0, chartWidth, chartHeight, nullptr));
  }

  if (this -> gridGroup == nullptr) {
    this -> gridGroup = ui -> chartField -> scene() -> createItemGroup({});
  }

  for (qint16 pointX = centerX + gridLengthX; pointX < chartWidth + 1; pointX += gridLengthX) { // Drawing grid's X axes.
    QPen* axisLinePen = new QPen();
    axisLinePen -> setColor(gridColor);
    axisLinePen -> setDashPattern(gridLine);

    QGraphicsLineItem* axisLineFirst = new QGraphicsLineItem(pointX, 0, pointX, chartHeight, nullptr);
    axisLineFirst -> setPen(*axisLinePen);

    QGraphicsLineItem* axisLineSecond = new QGraphicsLineItem(2 * centerX - pointX, 0, 2 * centerX - pointX, chartHeight, nullptr);
    axisLineSecond -> setPen(*axisLinePen);

    this -> gridGroup -> addToGroup(axisLineFirst);
    this -> gridGroup -> addToGroup(axisLineSecond);
  }

  for (qint16 pointY = centerY + gridLengthY; pointY < chartHeight + 1; pointY += gridLengthY) { // Drawing grid's Y axes.
    QPen* axisLinePen = new QPen();
    axisLinePen -> setColor(gridColor);
    axisLinePen -> setDashPattern(gridLine);

    QGraphicsLineItem* axisLineFirst = new QGraphicsLineItem(0, pointY, chartWidth, pointY, nullptr);
    axisLineFirst -> setPen(*axisLinePen);

    QGraphicsLineItem* axisLineSecond = new QGraphicsLineItem(0, 2 * centerY - pointY, chartWidth, 2 * centerY - pointY, nullptr);
    axisLineSecond -> setPen(*axisLinePen);

    this -> gridGroup -> addToGroup(axisLineFirst);
    this -> gridGroup -> addToGroup(axisLineSecond);
  }

  QString labelAxisX = "X: 1 [s / div]";
  QString labelAxisY = "Y: 1 [V / div]";

  ui -> labelChart -> setText(labelAxisX + '\n' + labelAxisY);
  ui -> labelChartCenter -> setText("Center: (0, 0)");
}

void Application::initTabOrder() {
  #define SET_TAB_ORDER(X, Y) ui -> pageMain -> setTabOrder(X, Y)

  SET_TAB_ORDER(ui -> textSineParameterAmplitude, ui -> textSineParameterFrequency);
  SET_TAB_ORDER(ui -> textSineParameterFrequency, ui -> textSineParameterPhase);
  SET_TAB_ORDER(ui -> textSineParameterPhase, ui -> textSineParameterConstant);
  SET_TAB_ORDER(ui -> textSineParameterConstant, ui -> buttonAddSine);

  SET_TAB_ORDER(ui -> buttonAddSine, ui -> textSquareParameterAmplitude);
  SET_TAB_ORDER(ui -> textSquareParameterAmplitude, ui -> textSquareParameterPeriod);
  SET_TAB_ORDER(ui -> textSquareParameterPeriod, ui -> textSquareParameterDutyCycle);
  SET_TAB_ORDER(ui -> textSquareParameterDutyCycle, ui -> textSquareParameterPhase);
  SET_TAB_ORDER(ui -> textSquareParameterPhase, ui -> textSquareParameterConstant);
  SET_TAB_ORDER(ui -> textSquareParameterConstant, ui -> buttonAddSquare);

  SET_TAB_ORDER(ui -> buttonAddSquare, ui -> textTriangularParameterAmplitude);
  SET_TAB_ORDER(ui -> textTriangularParameterAmplitude, ui -> textTriangularParameterDeadTime);
  SET_TAB_ORDER(ui -> textTriangularParameterDeadTime, ui -> textTriangularParameterPhase);
  SET_TAB_ORDER(ui -> textTriangularParameterPhase, ui -> textTriangularParameterConstant);
  SET_TAB_ORDER(ui -> textTriangularParameterConstant, ui -> textTriangularParameterEdgeRising);
  SET_TAB_ORDER(ui -> textTriangularParameterEdgeRising, ui -> textTriangularParameterEdgeFalling);
  SET_TAB_ORDER(ui -> textTriangularParameterEdgeFalling, ui -> buttonAddTriangular);

  SET_TAB_ORDER(ui -> buttonAddTriangular, ui -> buttonViewZoomIn);
  SET_TAB_ORDER(ui -> buttonViewZoomIn, ui -> buttonViewZoomOut);
  SET_TAB_ORDER(ui -> buttonViewZoomOut, ui -> buttonViewZoomReset);

  SET_TAB_ORDER(ui -> buttonViewZoomReset, ui -> listCharts);
  SET_TAB_ORDER(ui -> listCharts, ui -> buttonMenuDelete);
  SET_TAB_ORDER(ui -> buttonMenuDelete, ui -> buttonMenuRename);
  SET_TAB_ORDER(ui -> buttonMenuRename, ui -> buttonMenuMoreActions);

  SET_TAB_ORDER(ui -> buttonMenuMoreActions, ui -> buttonMoveUp);
  SET_TAB_ORDER(ui -> buttonMoveUp, ui -> buttonMoveRight);
  SET_TAB_ORDER(ui -> buttonMoveRight, ui -> buttonMoveDown);
  SET_TAB_ORDER(ui -> buttonMoveDown, ui -> buttonMoveLeft);
  SET_TAB_ORDER(ui -> buttonMoveLeft, ui -> buttonMoveCenter);

  #undef SET_TAB_ORDER
}

void Application::initToolbar() {
  QMenu* toolbarMenu = new QMenu("Title", this);

  actionList -> insert(MenuActions::MENU_ACTION_ADD, toolbarMenu -> addAction("Sum...", this, SLOT(menuAdd())));
  actionList -> value(MenuActions::MENU_ACTION_ADD) -> setEnabled(false);

  actionList -> insert(MenuActions::MENU_ACTION_SUBTRACT, toolbarMenu -> addAction("Subtract...", this, SLOT(menuSubtract())));
  actionList -> value(MenuActions::MENU_ACTION_SUBTRACT) -> setEnabled(false);

  ui -> buttonMenuMoreActions -> setMenu(toolbarMenu);
  ui -> buttonMenuMoreActions -> setContextMenuPolicy(Qt::ContextMenuPolicy::DefaultContextMenu);
}

void Application::initValues() {
  chartWidth = ui -> chartField -> width();
  chartHeight = ui -> chartField -> height();

  centerX = chartWidth / 2;
  centerY = chartHeight / 2;

  chartShiftX = chartShiftY = 0;
  gridLengthX = gridLengthY = 64;
  gridUnitX = gridUnitY = 1;
}
