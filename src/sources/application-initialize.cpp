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
