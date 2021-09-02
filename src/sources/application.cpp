#include "src/headers/application.h"
#include "ui_application.h"

Application::Application(QWidget* parent) : QMainWindow(parent), ui(new Ui::Application) {
  ui -> setupUi(this);

  initValues(); // Must be first to prepare all values for chart initialization.
  initChartField();
  initSlots();
  initToolbar();
  initTabOrder();
}

Application::~Application() {
  delete ui;
}

void Application::redrawAllCharts() {
  qreal argumentDelta = static_cast<qreal>(gridUnitX) / static_cast<qreal>(gridLengthX);
  qreal argumentMaximum = static_cast<qreal>(centerX) * argumentDelta;
  qreal argumentMinimum = -1.0 * argumentMaximum;

  QVector<qreal> arguments;

  QPen* chartColor = new QPen(QColor(255, 255, 255));
  QPen* chartColorSelected = new QPen(QColor(255, 128, 0));

  for (qreal argument = argumentMinimum; argument < argumentMaximum; argument += argumentDelta) { // Calculating arguments values list.
    arguments.append(argument - chartShiftX);
  }

  for (QString chartIdentifier : chartList -> keys()) {
    qDeleteAll(groupList -> value(chartIdentifier) -> childItems());
    chartList -> value(chartIdentifier) -> setArguments(arguments);
    QVector<qreal> values = chartList -> value(chartIdentifier) -> getValues(); // Retrieving computed functions values.

    for (qint32 point = 0; point < chartList -> value(chartIdentifier) -> signalLength() - 1; point++) {
      QGraphicsLineItem* line = new QGraphicsLineItem(point, centerY - (values[point] + chartShiftY) * (gridLengthY / gridUnitY), point + 1, centerY - (values[point + 1] + chartShiftY) * (gridLengthY / gridUnitY));

      if (chartList -> value(chartIdentifier) -> isSelected == true) {
        line -> setPen(*chartColorSelected);
      } else {
        line -> setPen(*chartColor);
      }

      groupList -> value(chartIdentifier) -> addToGroup(line);
    }
  }
}

void Application::updateAxesLabel() {
  QString labelX = QString("X: %1 [s / div]").arg(gridUnitX);
  QString labelY = QString("Y: %1 [V / div]").arg(gridUnitY);

  ui -> labelChart -> setText(labelX + '\n' + labelY);
}
